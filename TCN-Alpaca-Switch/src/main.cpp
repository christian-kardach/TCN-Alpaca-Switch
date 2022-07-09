#include <Arduino.h>
#include "configuration.hpp"

#include <ArduinoLog.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <arduino-timer.h>
#include <Redis.h>
#include <mDNSResolver.h>

#include "arduino_secrets.h"
#include "switchHandler.h"
#include "sensors/dh11Sensor.h"
#include "sensors/ina260Sensor.h"

using namespace mDNSResolver;

int status = WL_IDLE_STATUS;
///////enter your sensitive data in the Secret tab/arduino_secrets.h
char hostname[] = _HOSTNAME;
char ssid[] = _SSID;     // your network SSID (name)
char pass[] = _PASSWORD; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;        // your network key Index number (needed only for WEP)

unsigned int localPort = 32227;  // The Alpaca Discovery test port
unsigned int alpacaPort = 11111; // The (fake) port that the Alpaca API would be available on

char packetBuffer[255]; // buffer to hold incoming packet

ESP8266WebServer *server = new ESP8266WebServer(alpacaPort);

ESP8266HTTPUpdateServer updater;
WiFiUDP Udp;

// Redis
Resolver resolver(Udp);
bool redisConnected = false;
WiFiClient redisConn;
Redis *gRedis = nullptr;

SwitchHandler *device = new SwitchHandler(server);
DH11Sensor *dh11 = new DH11Sensor();
INA260Sensor *ina260 = new INA260Sensor();

auto timer = timer_create_default();

void CheckForDiscovery()
{
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Log.traceln("Received packet of size: %d" CR, packetSize);
    IPAddress remoteIp = Udp.remoteIP();
    Log.traceln("From %s , on port %d" CR, remoteIp.toString().c_str(), Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0)
    {
      // Ensure that it is null terminated
      packetBuffer[len] = 0;
    }
    Log.traceln("Contents: %s" CR, packetBuffer);

    // No undersized packets allowed
    if (len < 16)
    {
      return;
    }

    if (strncmp("alpacadiscovery1", packetBuffer, 16) != 0)
    {
      return;
    }

    char response[36] = {0};

    sprintf(response, "{\"AlpacaPort\": %d}", alpacaPort);

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(response);
    Udp.endPacket();
  }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Log.traceln(F("SSID: %s" CR), WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Log.traceln(F("IP Address: %s" CR), ip.toString().c_str());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Log.traceln("signal strength (RSSI): %l dBm" CR, rssi);
}

bool readSensors(void *)
{
  String temperatureReading = dh11->getReading();
  Log.infoln("DH11: %S" CR, temperatureReading);

  String powerReading = ina260->getReading();
  Log.infoln("INA260: %S" CR, powerReading);


  if (redisConnected)
  {
    gRedis->publish("app:notifications", temperatureReading.c_str());
    gRedis->publish("app:notifications", powerReading.c_str());
  }

  return true; // repeat? true
}

void connectToRedis()
{
  resolver.setLocalIP(WiFi.localIP());

  Serial.printf("Attempting to resolve %s\n", REDIS_ADDR);
  IPAddress answer = resolver.search(REDIS_ADDR);
  if(answer == IPADDR_NONE) {
    Serial.println("no answer found");
  } else {
    Serial.println("Gotta result!");
    Serial.println(answer);
  }

  // Redis
  String redishost = "192.168.1.208"; 
  if (!redisConn.connect(redishost, REDIS_PORT))
  {
    Serial.println("Failed to connect to the Redis server!");
    redisConnected = false;
  }
  else
  {
    gRedis = new Redis(redisConn);
    auto connRet = gRedis->authenticate(REDIS_PASSWORD);
    if (connRet == RedisSuccess)
    {
      Serial.printf("Connected to the Redis server at %s!\n", REDIS_ADDR);
      redisConnected = true;
    }
    else
    {
      Serial.printf("Failed to authenticate to the Redis server! Errno: %d\n", (int)connRet);
      redisConnected = false;
    } 
  }
}

void handleMgmtVersions() { device->handlerMgmtVersions(); }
void handleMgmtDescription() { device->handlerMgmtDescription(); }
void handleMgmtConfiguredDevices() { device->handlerMgmtConfiguredDevices(); }

void handleConnected() { device->handlerConnected(); }
void handleDescriptionGet() { device->handlerDescriptionGet(); }
void handleDriverInfoGet() { device->handlerDriverInfoGet(); }
void handleDriverVersionGet() { device->handlerDriverVersionGet(); }
void handleInterfaceVersionGet() { device->handlerInterfaceVersionGet(); }
void handleNameGet() { device->handlerNameGet(); }
void handleSupportedActionsGet() { device->handlerSupportedActionsGet(); }

void handleAction() { device->handleAction(); }
void handleCommandBlind() { device->handleCommandBlind(); }
void handleCommandBool() { device->handleCommandBool(); }
void handleCommandString() { device->handleCommandString(); }

void handleDriver0Maxswitch() { device->handlerDriver0Maxswitch(); }
void handleDriver0CanWrite() { device->handlerDriver0CanWrite(); }
void handleDriver0SwitchDescription() { device->handlerDriver0SwitchDescription(); }
void handleDriver0SwitchState() { device->handlerDriver0SwitchState(); }
void handleDriver0SwitchName() { device->handlerDriver0SwitchName(); }
void handleDriver0SwitchValue() { device->handlerDriver0SwitchValue(); }
void handleDriver0MinSwitchValue() { device->handlerDriver0MinSwitchValue(); }
void handleDriver0MaxSwitchValue() { device->handlerDriver0MaxSwitchValue(); }
void handleDriver0SwitchStep() { device->handlerDriver0SwitchStep(); }

/******************************************
 * SETUP
 ******************************************/
void setup()
{
  Serial.begin(9600);

  // Initialize with log level and log output.
  Log.begin(LOG_LEVEL_INFO, &Serial);

  Log.infoln("Connecting to WIFI...");

  // Some ESP8266 modules broadcast their own network, this turns that off
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);

  // attempt to connect to the Wifi network defined in arduino_secrets.h
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Log.traceln(".");
  }

  Log.infoln("Connected to wifi");
  printWifiStatus();

  // Management API
  server->on("/management/apiversions", HTTP_GET, handleMgmtVersions);
  server->on("/management/v1/description", HTTP_GET, handleMgmtDescription);
  server->on("/management/v1/configureddevices", HTTP_GET, handleMgmtConfiguredDevices);

  server->on("/api/v1/switch/0/connected", HTTP_ANY, handleConnected);
  server->on("/api/v1/switch/0/description", HTTP_GET, handleDescriptionGet);
  server->on("/api/v1/switch/0/driverinfo", HTTP_GET, handleDriverInfoGet);
  server->on("/api/v1/switch/0/driverversion", HTTP_GET, handleDriverVersionGet);
  server->on("/api/v1/switch/0/interfaceversion", HTTP_GET, handleInterfaceVersionGet);
  server->on("/api/v1/switch/0/name", HTTP_GET, handleNameGet);
  server->on("/api/v1/switch/0/supportedactions", HTTP_GET, handleSupportedActionsGet);

  server->on("/api/v1/switch/0/action", HTTP_PUT, handleAction);
  server->on("/api/v1/switch/0/commandblind", HTTP_PUT, handleCommandBlind);
  server->on("/api/v1/switch/0/commandbool", HTTP_PUT, handleCommandBool);
  server->on("/api/v1/switch/0/commandstring", HTTP_PUT, handleCommandString);

  // Switch-specific functions
  server->on("/api/v1/switch/0/maxswitch", HTTP_GET, handleDriver0Maxswitch);
  server->on("/api/v1/switch/0/canwrite", HTTP_GET, handleDriver0CanWrite);
  server->on("/api/v1/switch/0/getswitchdescription", HTTP_GET, handleDriver0SwitchDescription);
  server->on("/api/v1/switch/0/getswitch", HTTP_GET, handleDriver0SwitchState);
  server->on("/api/v1/switch/0/setswitch", HTTP_PUT, handleDriver0SwitchState);
  server->on("/api/v1/switch/0/getswitchname", HTTP_GET, handleDriver0SwitchName);
  server->on("/api/v1/switch/0/setswitchname", HTTP_PUT, handleDriver0SwitchName);
  server->on("/api/v1/switch/0/getswitchvalue", HTTP_GET, handleDriver0SwitchValue);
  server->on("/api/v1/switch/0/setswitchvalue", HTTP_PUT, handleDriver0SwitchValue);
  server->on("/api/v1/switch/0/minswitchvalue", HTTP_GET, handleDriver0MinSwitchValue);
  server->on("/api/v1/switch/0/maxswitchvalue", HTTP_GET, handleDriver0MaxSwitchValue);
  server->on("/api/v1/switch/0/switchstep", HTTP_GET, handleDriver0SwitchStep);

  /*
  //Custom
  server.on("/status",                              HTTP_GET, handlerStatus);
  server.on("/restart",                             HTTP_ANY, handlerRestart);
  */

  updater.setup(server);
  server->begin();
  Log.infoln("Alpaca server handlers setup & started...");
  Log.infoln("Listening for Alpaca discovery requests...");

  Udp.begin(localPort);

  connectToRedis();

  timer.every(1000, readSensors);
}

void loop()
{

  server->handleClient();
  CheckForDiscovery();
  timer.tick();
}