#include "switchHandler.h"


SwitchHandler::SwitchHandler(ESP8266WebServer *server)
{
    _server = server;
    switchDevice = new SwitchDevice();
    serverTransactionID = 0;
}

void SwitchHandler::debugServerQuery()
{
    for (int i = 0; i < _server->args(); i++) {
        Log.noticeln("%d" CR, i);
        Log.noticeln("%s" CR, _server->argName(i));
        Log.noticeln("%s" CR, _server->arg(i));
        Log.noticeln("--------------------------");
    }
}

void SwitchHandler::incrementServerTransID()
{
    serverTransactionID++;
}

void SwitchHandler::returnEmpty(String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.noticeln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnBoolValue(bool val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.noticeln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnStringValue(String val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.noticeln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnIntValue(int val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.noticeln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnFloatValue(float val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.noticeln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnJsonArrayValue(JsonArray val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.noticeln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnDoubleValue(double val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.noticeln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}
/*
 * ALPACA DEVICE MANAGEMENT
 */

void SwitchHandler::handlerMgmtVersions()
{
    Log.noticeln("handlerMgmtVersions called...");
    incrementServerTransID();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(1);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(1);
        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.noticeln(F("Returning: %s" CR), output.c_str());
        // return output;
        _server->send(200, "text/json", output);
        // sendDeviceSetup( returnCode, message, err );
        
    }
}

void SwitchHandler::handlerMgmtDescription()
{
    Log.noticeln("handlerMgmtDescription called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);

        val["ServerName"] = SERVER_NAME; //"TCN Mount Switch";
        val["Manufacturer"] = MANUFACTURER; // "Christian Kardach";
        val["ManufacturerVersion"] = MANUFACTURER_VERSION; //"1.0";
        val["Location"] = LOCATION; //"SE";

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        //returnJsonArrayValue(array);
        
        DynamicJsonDocument doc(1024);
        doc["Value"] = val;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.noticeln(F("Returning: %s" CR), output.c_str());
        _server->send(200, "text/json", output);
        
    }
}

void SwitchHandler::handlerMgmtConfiguredDevices()
{
    Log.noticeln("handlerMgmtConfiguredDevices called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;

        val["DeviceName"] = DEVICE_NAME; //"TCN Mount Switch";
        val["DeviceType"] = DEVICE_TYPE; //"Switch";
        val["DeviceNumber"] = DEVICE_NR; //0;
        val["UniqueID"] = UNIQUE_CLIENT_ID;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.noticeln(F("Returning: %s" CR), output.c_str());

        _server->send(200, "text/json", output);
        
    }
}

void SwitchHandler::handlerConnected()
{
    Log.noticeln("handlerConnected called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.noticeln("handlerConnected GET called");

        String deviceType = _server->arg("device_type");
        //uint32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

        returnBoolValue(switchDevice->connected, "", 0);
    }

    if (_server->method() == HTTP_PUT)
    {
        Log.noticeln("handlerConnected POST called");

        // String _connected = _server->arg("Connected");
        switchDevice->connected = (bool)_server->arg("Connected");
        // Log.noticeln("%t", CR, switchDevice->connected);

        returnEmpty("", 0);
    }
}

/***********************************
 * ASCOM STANDARD
 **********************************/
void SwitchHandler::handlerDescriptionGet()
{
    Log.noticeln("handlerDescriptionGet called");
    returnStringValue(DESCRIPTION, "", 0);
}

void SwitchHandler::handlerDriverInfoGet()
{
    Log.noticeln("handlerDriverInfoGet called");
    returnStringValue(DRIVER_INFO, "", 0);
}

void SwitchHandler::handlerDriverVersionGet()
{
    Log.noticeln("handlerDriverVersionGet called");
    returnStringValue(DRIVER_VERSION, "", 0);
}

void SwitchHandler::handlerInterfaceVersionGet()
{
    Log.noticeln("handlerInterfaceVersionGet called");
    returnIntValue(1, "", 0);
}

void SwitchHandler::handlerNameGet()
{
    Log.noticeln("handlerNameGet called");
    returnStringValue(DEVICE_NAME, "", 0);
}

void SwitchHandler::handlerSupportedActionsGet()
{
    Log.noticeln("handlerSupportedActionsGet called");

    DynamicJsonDocument val(1024);
    const size_t CAPACITY = JSON_ARRAY_SIZE(13);
    StaticJsonDocument<CAPACITY> devices;
    JsonArray array = devices.to<JsonArray>();
    
    array.add("action");
    array.add("commandblind");
    array.add("commandbool");
    array.add("commandstring");
    array.add("maxswitch");
    array.add("canwrite");
    array.add("getswitchdescription");
    array.add("getswitch");
    array.add("getswitchname");
    array.add("getswitchvalue");
    array.add("minswitchvalue");
    array.add("maxswitchvalue");
    array.add("switchstep");

    returnJsonArrayValue(array, "", 0);
    
}

void SwitchHandler::handleAction()
{
    Log.noticeln("handleAction called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    //u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String action = _server->arg("Action");
    String parameters = _server->arg("Parameters");

    returnStringValue("ok", "", 0);
}

void SwitchHandler::handleCommandBlind()
{
    Log.noticeln("handleCommandBlind called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.noticeln("%s" CR, command);
    Log.noticeln("%s" CR, raw);

    returnEmpty("", 0);
}

void SwitchHandler::handleCommandBool()
{
    Log.noticeln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.noticeln("%s" CR, command);
    Log.noticeln("%s" CR, raw);

    returnBoolValue(true, "", 0);
}

void SwitchHandler::handleCommandString()
{
    Log.noticeln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.noticeln("%s" CR, command.c_str());
    Log.noticeln("%s" CR, raw.c_str());

    returnStringValue("ok", "", 0);
}

/***********************************
 * ASCOM SWITCH
 **********************************/
void SwitchHandler::handlerDriver0Maxswitch()
{
    Log.noticeln("handlerDriver0Maxswitch called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnIntValue(NR_OF_RELAYS, "", 0);
}

void SwitchHandler::handlerDriver0CanWrite()
{
    Log.noticeln("handlerDriver0CanWrite called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnBoolValue(true, "", 0);
}

void SwitchHandler::handlerDriver0SwitchDescription()
{
    Log.noticeln("handlerDriver0SwitchDescription called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnStringValue("Switch Description", "", 0);
}

void SwitchHandler::handlerDriver0SwitchState()
{
    Log.noticeln("handlerDriver0SwitchState called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.noticeln("GET SwitchState called");
        if(id == 0)
        {
            returnBoolValue(switchDevice->relayState0, "", 0);
        }
        else if(id == 1)
        {
            returnBoolValue(switchDevice->relayState1, "", 0);
        }
        else if(id == 2)
        {
            returnBoolValue(switchDevice->relayState2, "", 0);
        }
        else if(id == 3)
        {
            returnBoolValue(switchDevice->relayState3, "", 0);
        }
     
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.noticeln("PUT SwitchState called");
        bool val = (bool)_server->arg("State");

        if(id == 0)
        {
            switchDevice->relayState0 = val;
            returnEmpty("", 0);
        }
        else if(id == 1)
        {
            switchDevice->relayState1 = val;
            returnEmpty("", 0);
        }
        else if(id == 2)
        {
            switchDevice->relayState2 = val;
            returnEmpty("", 0);
        }
        else if(id == 3)
        {
            switchDevice->relayState3 = val;
            returnEmpty("", 0);
        }
    }

}

void SwitchHandler::handlerDriver0SwitchName()
{
    Log.noticeln("handlerDriver0SwitchName called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if(id == 0)
    {
        returnStringValue(RELAY_1_NAME, "", 0);
    }
    else if(id == 1)
    {
        returnStringValue(RELAY_2_NAME, "", 0);
    }
    else if(id == 2)
    {
        returnStringValue(RELAY_3_NAME, "", 0);
    }
    else if(id == 3)
    {
        returnStringValue(RELAY_4_NAME, "", 0);
    }
}

void SwitchHandler::handlerDriver0SwitchValue()
{
    Log.noticeln("handlerDriver0SwitchValue called");
    //debugServerQuery();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.noticeln("GET SwitchValue called");
        if(id == 0)
        {
            returnDoubleValue(switchDevice->relayValue0, "", 0);
        }
        else if(id == 1)
        {
            returnDoubleValue(switchDevice->relayValue1, "", 0);
        }
        else if(id == 2)
        {
            returnDoubleValue(switchDevice->relayValue2, "", 0);
        }
        else if(id == 3)
        {
            returnDoubleValue(switchDevice->relayValue3, "", 0);
        }
     
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.noticeln("PUT SwitchValue called");
        double val = (double)_server->arg("Value").toDouble();
        
        if(id == 0)
        {
            switchDevice->relayValue0 = val;
            returnEmpty("", 0);
        }
        else if(id == 1)
        {
            switchDevice->relayValue1 = val;
            returnEmpty("", 0);
        }
        else if(id == 2)
        {
            switchDevice->relayValue2 = val;
            returnEmpty("", 0);
        }
        else if(id == 3)
        {
            switchDevice->relayValue3 = val;
            returnEmpty("", 0);
        }
    }


}

void SwitchHandler::handlerDriver0MinSwitchValue()
{
    Log.noticeln("handlerDriver0MinSwitchValue called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(0.0, "", 0);
}

void SwitchHandler::handlerDriver0MaxSwitchValue()
{
    Log.noticeln("handlerDriver0MaxSwitchValue called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(1.0, "", 0);
}

void SwitchHandler::handlerDriver0SwitchStep()
{
    Log.noticeln("handlerDriver0SwitchStep called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(1.0, "", 0);
}