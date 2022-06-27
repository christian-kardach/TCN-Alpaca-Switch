#include "switchDevice.h"


SwitchDevice::SwitchDevice()
{
    pinMode(RELAY_PIN_1, OUTPUT);
    pinMode(RELAY_PIN_2, OUTPUT);
    pinMode(RELAY_PIN_3, OUTPUT);
    pinMode(RELAY_PIN_4, OUTPUT);
}

void SwitchDevice::setRelayState(int relayNr, bool state)
{
    Log.traceln("Relay nr: %d" CR, relayNr);
    switch (relayNr)
    {
    case 0:
        if(state == true)
        {
            digitalWrite(RELAY_PIN_1, HIGH);
            relayState0 = true;
            relayValue0 = 1.0;
        }
        else{
            digitalWrite(RELAY_PIN_1, LOW);
            relayState0 = false;
            relayValue0 = 0.0;
        }
        break;
    case 1:
        if(state == true)
        {
            digitalWrite(RELAY_PIN_2, HIGH);
            relayState1 = true;
            relayValue1 = 1.0;
        }
        else{
            digitalWrite(RELAY_PIN_2, LOW);
            relayState1 = false;
            relayValue1 = 0.0;
        }
        break;
    case 2:
        if(state == true)
        {
            digitalWrite(RELAY_PIN_3, HIGH);
            relayState2 = true;
            relayValue2 = 1.0;
        }
        else{
            digitalWrite(RELAY_PIN_3, LOW);
            relayState2 = false;
            relayValue2 = 0.0;
        }
        break;
    case 3:
        if(state == true)
        {
            digitalWrite(RELAY_PIN_4, HIGH);
            relayState3 = true;
            relayValue3 = 1.0;
        }
        else{
            digitalWrite(RELAY_PIN_4, LOW);
            relayState3 = false;
            relayValue3 = 1.0;
        }
        break;
    default:
        break;
    }
}

void SwitchDevice::setRelayValue(int relayNr, double value)
{
    switch (relayNr)
    {
    case 0:
        if(value == 1.0)
        {
            digitalWrite(RELAY_PIN_1, HIGH);
            relayState0 = true;
            relayValue0 = value;
        }
        else{
            digitalWrite(RELAY_PIN_1, LOW);
            relayState0 = false;
            relayValue0 = value;
        }
        break;
    case 1:
        if(value == 1.0)
        {
            digitalWrite(RELAY_PIN_2, HIGH);
            relayState1 = true;
            relayValue1 = value;
        }
        else{
            digitalWrite(RELAY_PIN_2, LOW);
            relayState1 = false;
            relayValue1 = value;
        }
        break;
    case 2:
        if(value == 1.0)
        {
            digitalWrite(RELAY_PIN_3, HIGH);
            relayState2 = true;
            relayValue2 = value;
        }
        else{
            digitalWrite(RELAY_PIN_3, LOW);
            relayState2 = false;
            relayValue2 = value;
        }
        break;
    case 3:
        if(value == 1.0)
        {
            digitalWrite(RELAY_PIN_4, HIGH);
            relayState3 = true;
            relayValue3 = value;
        }
        else{
            digitalWrite(RELAY_PIN_4, LOW);
            relayState3 = false;
            relayValue3 = value;
        }
        break;
    default:
        break;
    }
}