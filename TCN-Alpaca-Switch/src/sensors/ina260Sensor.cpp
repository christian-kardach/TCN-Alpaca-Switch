#include "sensors/ina260Sensor.h"

INA260Sensor::INA260Sensor()
{
    INA260Sensor::ina260 = new Adafruit_INA260();
    current = 0.0f;
    voltage = 0.0f;
    power = 0.0f;
}

String INA260Sensor::getReading()
{
    current = ina260->readCurrent();
    voltage = ina260->readBusVoltage();
    power = ina260->readPower();

    DynamicJsonDocument doc(1024);
    doc["sensor"] = "power";
    doc["current"] = current;
    doc["voltage"] = voltage;
    doc["power"] = power;

    String output;
    serializeJson(doc, output);
    return output;
}