#ifndef SWITCHHANDLER_H
#define SWITCHHANDLER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoJson.h>
#include "switchDevice.h"

class SwitchHandler
{
    ESP8266WebServer* _server;

    public:
        SwitchHandler(ESP8266WebServer* server);
        
        

        void handlerMgmtVersions();
        void handlerMgmtDescription();
        void handlerMgmtConfiguredDevices();

        void handlerConnected();
        void handlerDescriptionGet();
        void handlerDriverInfoGet();
        void handlerDriverVersionGet();
        void handlerInterfaceVersionGet();
        void handlerNameGet();
        void handlerSupportedActionsGet();

        void handleAction();
        void handleCommandBlind();
        void handleCommandBool();
        void handleCommandString();


        void handlerDriver0Maxswitch();
        void handlerDriver0CanWrite();
        void handlerDriver0SwitchDescription();
        void handlerDriver0SwitchState();
        void handlerDriver0SwitchName();
        void handlerDriver0SwitchValue();
        void handlerDriver0MinSwitchValue();
        void handlerDriver0MaxSwitchValue();
        void handlerDriver0SwitchStep();

        /*
        //Common
        void handlerAction(ESP8266WebServer &server);
        void handlerCommandBlind(ESP8266WebServer &server);
        void handlerCommandBool(ESP8266WebServer &server);
        void handlerCommandString(ESP8266WebServer &server);
        void handlerConnected(ESP8266WebServer &server);
        void handlerDescriptionGet(ESP8266WebServer &server);
        void handlerDriverInfoGet(ESP8266WebServer &server);
        void handlerDriverVersionGet(ESP8266WebServer &server);
        void handlerInterfaceVersionGet(ESP8266WebServer &server);
        void handlerNameGet(ESP8266WebServer &server);
        void handlerSupportedActionsGet(ESP8266WebServer &server);



        //Driver0 settings
        void handlerDriver0Setup(void);
        void handlerDriver0SetupNumSwitches(void);
        void handlerDriver0Maxswitch(void);
        void handlerDriver0CanWrite(void);
        void handlerDriver0SwitchState(void);
        void handlerDriver0SwitchDescription(void);
        void handlerDriver0SwitchName(void);
        void handlerDriver0SwitchType(void);
        void handlerDriver0SwitchValue(void);
        void handlerDriver0MinSwitchValue(void);
        void handlerDriver0MaxSwitchValue(void);
        void handlerDriver0SwitchStep(void);
        void handlerDriver0SetupSwitches(void);

        void handlerNotFound();
        void handlerRestart();
        void handlerNotImplemented();
        void handlerStatus(void);
        */
    
    private:
        uint32_t transID;
        uint32_t clientID;
        String uniqueID = "4431281c-8560-4ad7-982f-5a6e507dda19";

        SwitchDevice* switchDevice;

        void returnEmpty();

        void returnStringValue(String val);
        void returnBoolValue(bool val);
        void returnIntValue(int val);
        void returnFloatValue(float val);
        void returnJsonArrayValue(JsonArray val);
        void returnDoubleValue(double val);

        void debugServerQuery();
        
};
#endif