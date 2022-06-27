#ifndef SWITCHDEVICE_H
#define SWITCHDEVICE_H

#include <Arduino.h>

class SwitchDevice
{
    public:
    SwitchDevice();

    bool connected = false;
    String uniqueID = "4431281c-8560-4ad7-982f-5a6e507dda19";

    bool relayState0 = false;
    bool relayState1 = false;
    bool relayState2 = false;
    bool relayState3 = false;

    double relayValue0 = 0.0;
    double relayValue1 = 0.0;
    double relayValue2 = 0.0;
    double relayValue3 = 0.0;

    void setRelayState(int relayNr, bool state);
    void setRelayValue(int relayNr, double value);

    private:
};

#endif