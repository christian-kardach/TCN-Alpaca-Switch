#include "switchHandler.h"


SwitchHandler::SwitchHandler(ESP8266WebServer *server)
{
    _server = server;
    switchDevice = new SwitchDevice();
}

void SwitchHandler::debugServerQuery()
{
    for (int i = 0; i < _server->args(); i++) {
        Serial.println((String)i);
        Serial.println(_server->argName(i));
        Serial.println(_server->arg(i));
        Serial.println("--------------------------");    
    }
}

void SwitchHandler::returnEmpty()
{
    DynamicJsonDocument doc(1024);

    doc["ErrorMessage"] = "";
    doc["ErrorNumber"] = 0;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = 0;

    String output;
    serializeJson(doc, output);

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnBoolValue(bool val)
{
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = "";
    doc["ErrorNumber"] = 0;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = 0;

    String output;
    serializeJson(doc, output);

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnStringValue(String val)
{
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = "";
    doc["ErrorNumber"] = 0;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = 0;

    String output;
    serializeJson(doc, output);

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnIntValue(int val)
{
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = "";
    doc["ErrorNumber"] = 0;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = 0;

    String output;
    serializeJson(doc, output);

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnFloatValue(float val)
{
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = "";
    doc["ErrorNumber"] = 0;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = 0;

    String output;
    serializeJson(doc, output);

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnJsonArrayValue(JsonArray val)
{
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = "";
    doc["ErrorNumber"] = 0;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = 0;

    String output;
    serializeJson(doc, output);

    _server->send(200, "text/json", output);
}

void SwitchHandler::returnDoubleValue(double val)
{
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = "";
    doc["ErrorNumber"] = 0;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = 0;

    String output;
    serializeJson(doc, output);

    _server->send(200, "text/json", output);
}
/*
 * ALPACA DEVICE MANAGEMENT
 */

void SwitchHandler::handlerMgmtVersions()
{

    Serial.println("handlerMgmtVersions");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(1);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(1);

        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = 0;

        String output;
        serializeJson(doc, output);
        // return output;
        _server->send(200, "text/json", output);
        // sendDeviceSetup( returnCode, message, err );
    }
}

void SwitchHandler::handlerMgmtDescription()
{
    Serial.println("handlerMgmtDescription");

    String timeString, message, err;
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        DynamicJsonDocument val(1024);

        val["ServerName"] = "TCN Mount Switch";
        val["Manufacturer"] = "Christian Kardach";
        val["ManufacturerVersion"] = "1.0";
        val["Location"] = "SE";

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        DynamicJsonDocument doc(1024);
        doc["Value"] = val;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = 0;

        String output;
        serializeJson(doc, output);
        _server->send(200, "text/json", output);
    }
}

void SwitchHandler::handlerMgmtConfiguredDevices()
{
    Serial.println("handlerMgmtConfiguredDevices");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        DynamicJsonDocument val(1024);
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;

        val["DeviceName"] = "TCN Mount Switch";
        val["DeviceType"] = "Switch";
        val["DeviceNumber"] = 0;
        val["UniqueID"] = uniqueID;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = 0;

        String output;
        serializeJson(doc, output);

        _server->send(200, "text/json", output);
    }
}

void SwitchHandler::handlerConnected()
{
    Serial.println("handlerConnected");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Serial.println("handlerConnected GET");

        String deviceType = _server->arg("device_type");
        uint32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

        returnBoolValue(switchDevice->connected);
    }

    if (_server->method() == HTTP_PUT)
    {
        Serial.println("handlerConnected POST");

        // String _connected = _server->arg("Connected");
        switchDevice->connected = (bool)_server->arg("Connected");
        Serial.println(switchDevice->connected);

        returnEmpty();
    }
}

void SwitchHandler::handlerDescriptionGet()
{
    Serial.println("handlerDescriptionGet");
    returnStringValue("TCN Mount Switch");
}

void SwitchHandler::handlerDriverInfoGet()
{
    Serial.println("handlerDriverInfoGet");
    returnStringValue("Custom driver");
}

void SwitchHandler::handlerDriverVersionGet()
{
    Serial.println("handlerDriverVersionGet");
    returnFloatValue(1.0f);
}

void SwitchHandler::handlerInterfaceVersionGet()
{
    Serial.println("handlerInterfaceVersionGet");
    returnIntValue(1);
}

void SwitchHandler::handlerNameGet()
{
    Serial.println("handlerNameGet");
    returnStringValue("TCN Mount Switch");
}

void SwitchHandler::handlerSupportedActionsGet()
{
    Serial.println("handlerSupportedActionsGet");

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

    returnJsonArrayValue(array);
    
}

/***********************************
 * ASCOM STANDARD
 **********************************/
void SwitchHandler::handleAction()
{
    Serial.println("handleAction");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String action = _server->arg("Action");
    String parameters = _server->arg("Parameters");

    Serial.println(action);
    Serial.println(parameters);

    returnStringValue("ok");
    
}

void SwitchHandler::handleCommandBlind()
{
    Serial.println("handleCommandBlind");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Serial.println(command);
    Serial.println(raw);

    returnEmpty();
}

void SwitchHandler::handleCommandBool()
{
    Serial.println("handleCommandBool");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Serial.println(command);
    Serial.println(raw);

    returnBoolValue(true);
}

void SwitchHandler::handleCommandString()
{
    Serial.println("handleCommandBool");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Serial.println(command);
    Serial.println(raw);

    returnStringValue("ok");
}

/***********************************
 * ASCOM SWITCH
 **********************************/
void SwitchHandler::handlerDriver0Maxswitch()
{
    Serial.println("handlerDriver0Maxswitch");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnIntValue(4);
}

void SwitchHandler::handlerDriver0CanWrite()
{
    Serial.println("handlerDriver0CanWrite");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnBoolValue(true);
}

void SwitchHandler::handlerDriver0SwitchDescription()
{
    Serial.println("handlerDriver0SwitchDescription");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    Serial.println(id);

    returnStringValue("Switch Description");
}

void SwitchHandler::handlerDriver0SwitchState()
{
    Serial.println("handlerDriver0SwitchState");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    Serial.println(id);

    if (_server->method() == HTTP_GET)
    {
        Serial.println("GET SwitchState");
        if(id == 0)
        {
            returnBoolValue(switchDevice->relayState0);
        }
        else if(id == 1)
        {
            returnBoolValue(switchDevice->relayState1);
        }
        else if(id == 2)
        {
            returnBoolValue(switchDevice->relayState2);
        }
        else if(id == 3)
        {
            returnBoolValue(switchDevice->relayState3);
        }
     
    }
    else if (_server->method() == HTTP_PUT)
    {
        Serial.println("PUT SwitchState");
        bool val = (bool)_server->arg("State");
        Serial.println(val);

        if(id == 0)
        {
            switchDevice->relayState0 = val;
            returnEmpty();
        }
        else if(id == 1)
        {
            switchDevice->relayState1 = val;
            returnEmpty();
        }
        else if(id == 2)
        {
            switchDevice->relayState2 = val;
            returnEmpty();
        }
        else if(id == 3)
        {
            switchDevice->relayState3 = val;
            returnEmpty();
        }
    }


    //returnBoolValue(false);
}

void SwitchHandler::handlerDriver0SwitchName()
{
    Serial.println("handlerDriver0SwitchName");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    // Serial.println(deviceNumber);
    Serial.println(id);

    if(id == 0)
    {
        Serial.println("TestSwitch 0");
        returnStringValue("TestSwitch 0");
    }
    else if(id == 1)
    {
        Serial.println("TestSwitch 1");
        returnStringValue("TestSwitch 1");
    }
    else if(id == 2)
    {
        Serial.println("TestSwitch 2");
        returnStringValue("TestSwitch 2");
    }
    else if(id == 3)
    {
        Serial.println("TestSwitch 3");
        returnStringValue("TestSwitch 3");
    }
    else
    {
        Serial.println("TestSwitch");
        returnStringValue("TestSwitch");
    }
   
}

void SwitchHandler::handlerDriver0SwitchValue()
{
    Serial.println("handlerDriver0SwitchValue");
    //debugServerQuery();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Serial.println("GET SwitchValue");
        if(id == 0)
        {
            returnDoubleValue(switchDevice->relayValue0);
        }
        else if(id == 1)
        {
            returnDoubleValue(switchDevice->relayValue1);
        }
        else if(id == 2)
        {
            returnDoubleValue(switchDevice->relayValue2);
        }
        else if(id == 3)
        {
            returnDoubleValue(switchDevice->relayValue3);
        }
     
    }
    else if (_server->method() == HTTP_PUT)
    {
        Serial.println("PUT SwitchValue");
        double val = (double)_server->arg("Value").toDouble();
        Serial.println(val);

        if(id == 0)
        {
            switchDevice->relayValue0 = val;
            returnEmpty();
        }
        else if(id == 1)
        {
            switchDevice->relayValue1 = val;
            returnEmpty();
        }
        else if(id == 2)
        {
            switchDevice->relayValue2 = val;
            returnEmpty();
        }
        else if(id == 3)
        {
            switchDevice->relayValue3 = val;
            returnEmpty();
        }
    }
    

}

void SwitchHandler::handlerDriver0MinSwitchValue()
{
    Serial.println("handlerDriver0MinSwitchValue");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    Serial.println(id);

    returnDoubleValue(0.0);
}

void SwitchHandler::handlerDriver0MaxSwitchValue()
{
    Serial.println("handlerDriver0MaxSwitchValue");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    Serial.println(id);

    returnDoubleValue(1.0);
}

void SwitchHandler::handlerDriver0SwitchStep()
{
    Serial.println("handlerDriver0SwitchStep");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    Serial.println(id);

    returnDoubleValue(1.0);
}