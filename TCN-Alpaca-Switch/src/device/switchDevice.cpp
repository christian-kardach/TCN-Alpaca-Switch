#include "device\switchDevice.h"

SwitchDevice::SwitchDevice()
{
    pinMode(RELAY_DATA_PIN, OUTPUT);
    pinMode(RELAY_LATCH_PIN, OUTPUT);
    pinMode(RELAY_CLOCK_PIN, OUTPUT);
    pinMode(RELAY_OE_PIN, OUTPUT);

    // writeRelayData(0, 0, 0.0);
    //readEEPROM();
    
    for(int i = NR_OF_RELAYS-1; i >=  0; i--){
        registers[i] = false; //LOW;
    }
    writeRelayData(0, false, 0.0);

#ifdef RELAY_PIN_0
    pinMode(RELAY_PIN_0, OUTPUT);
#endif
#ifdef RELAY_PIN_1
    pinMode(RELAY_PIN_1, OUTPUT);
#endif
#ifdef RELAY_PIN_2
    pinMode(RELAY_PIN_2, OUTPUT);
#endif
#ifdef RELAY_PIN_3
    pinMode(RELAY_PIN_3, OUTPUT);
#endif
#ifdef RELAY_PIN_4
    pinMode(RELAY_PIN_4, OUTPUT);
#endif
#ifdef RELAY_PIN_5
    pinMode(RELAY_PIN_5, OUTPUT);
#endif
#ifdef RELAY_PIN_6
    pinMode(RELAY_PIN_6, OUTPUT);
#endif
#ifdef RELAY_PIN_7
    pinMode(RELAY_PIN_7, OUTPUT);
#endif

}

void SwitchDevice::readEEPROM()
{
    Log.traceln("readEEPROM called");
    EEPROM.begin(EEPROM_SIZE);
    int address = 0;
    for(int i = 0; i < NR_OF_RELAYS; i++)
    {
        String channelName;
        EEPROM.get(address, channelName);
        Serial.println(channelName);
        channelNames[i] = channelName;
        address += sizeof(channelName); //update address value
    }
    EEPROM.end();
}

void SwitchDevice::writeEEPROM()
{
    EEPROM.begin(EEPROM_SIZE);
    int address = 0;
    for(int i = 0; i < NR_OF_RELAYS; i++)
    {
        EEPROM.put(address, channelNames[i]);
        address += sizeof(channelNames[i]); //update address value
    }
    EEPROM.commit();
}

void SwitchDevice::writeRelayData(int relay, int boolValue, double doubleValue)
{
    Log.traceln(F("writeRelayData nr: %d %T" CR), relay, boolValue);
    registers[relay] = boolValue;
    
    digitalWrite(RELAY_LATCH_PIN, LOW);
    for(int i = NR_OF_RELAYS-1; i >=  0; i--)
    {
        digitalWrite(RELAY_CLOCK_PIN, LOW); int val = registers[i];
        digitalWrite(RELAY_DATA_PIN, val);
        digitalWrite(RELAY_CLOCK_PIN, HIGH);
    }
    digitalWrite(RELAY_LATCH_PIN, HIGH);
    /*
    if(boolValue == false)
    {
            relayData = 0b0000000000000000;
    }
    else
    {
            relayData = 0b0000000000000001;
    }
    
    #if USE_BITSHIFT == 1
    // uint16_t Data = 0b0000000000000001;     

    digitalWrite(RELAY_LATCH_PIN, LOW);
    shiftOut(RELAY_DATA_PIN, RELAY_CLOCK_PIN, MSBFIRST, (relayData >> 8));
    shiftOut(RELAY_DATA_PIN, RELAY_CLOCK_PIN, MSBFIRST, relayData);
    digitalWrite(RELAY_LATCH_PIN, HIGH);
    
    #endif
    */
    #if USE_BITSHIFT != 1
    switch (relay)
    {
    case 0:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_0, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_0, LOW);
        }
        break;
    case 1:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_1, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_1, LOW);
        }
        break;
    case 2:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_2, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_2, LOW);
        }
        break;
    case 3:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_3, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_3, LOW);
        }
        break;
    case 4:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_4, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_4, LOW);
        }
        break;
    case 5:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_5, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_5, LOW);
        }
        break;
    case 6:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_6, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_6, LOW);
        }
        break;
    case 7:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_7, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_7, LOW);
        }
        break;
    default:
        break;
    }
    #endif
    relayStateBool[relay] = boolValue;
    relayStateValue[relay] = doubleValue;
}


void SwitchDevice::setRelayState(int relayNr, bool state)
{
    Log.traceln(F("Relay nr: %d %T" CR), relayNr, state);
    
    if(state == 1)
    {
        writeRelayData(relayNr, true, 1.0);
    }
    else {
        writeRelayData(relayNr, false, 0.0);
    }
    
}

void SwitchDevice::setRelayValue(int relayNr, double value)
{
    Log.traceln(F("Relay nr: %d %D" CR), relayNr, value);
    
    if(value > 0.0)
    {
        registers[relayNr] = true;
        
    }
    else {
        writeRelayData(relayNr, false, 0.0);
    }
    
}

bool SwitchDevice::getRelayState(int idx)
{
    return registers[idx];
}