#include "dh11Sensor.h"

DH11Sensor::DH11Sensor()
{
    DH11Sensor::dht = new DHT(DHT_PIN, DHT11);
    t = 0.0f;
    h = 0.0f;
}

void DH11Sensor::setup()
{
}

float DH11Sensor::getTemperature()
{
    float tRead = dht->readTemperature();
    if (!isnan(tRead))
    {
        t = tRead;
    }
    return t;
}

float DH11Sensor::getHumidity()
{
    float hRead = dht->readHumidity();
    if (!isnan(hRead))
    {
        t = hRead;
    }
    return t;
}

String DH11Sensor::getReading()
{
    getTemperature();
    getHumidity();

    DynamicJsonDocument doc(1024);
    doc["sensor"] = "SwitchTemperature";
    doc["temperature"] = t;
    doc["humidity"] = h;

    String output;
    serializeJson(doc, output);
    return output;
    
}