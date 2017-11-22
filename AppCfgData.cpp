/* ************************************************************************ */
/*
    AppCfgData.cpp - Intended to provide application configuration data, this
    could be things such as - 

        1) Application name
        2) Feature control flags. A "debug mute" is implemented here.
        3) Text message (be careful to not use too much memory!) content.

*/
#include "AppCfgData.h"
#include <ArduinoJson.h>

//////////////////////////////////////////////////////////////////////////////
/*
    Constructor
*/
AppCfgData::AppCfgData(const char *cfgfile): ConfigData(cfgfile)
{
    debugmute = false;
    appname = "";
}

//////////////////////////////////////////////////////////////////////////////
/*
    Parse the JSON data that is specific to this configuration object.
*/
void AppCfgData::parseJSON(std::unique_ptr<char[]>& buf)
{
    // This will always print, we can't use the debug mute flag
    // because it hasn't been read & parsed yet.
    Serial.println();
    Serial.println("AppCfgData parsing JSON - ");
    Serial.println(buf.get());
 
    // For getting the size correct, use the following to calculate
    // how much is requried for a given bit of JSON data - 
    //
    //      https://bblanchon.github.io/ArduinoJson/assistant/
    const size_t bufferSize = JSON_OBJECT_SIZE(3) + 54;
    StaticJsonBuffer<bufferSize> jsonBuffer;

    JsonObject& json = jsonBuffer.parseObject(buf.get());

    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        Another place is in AppCfgData.h
    */
    debugmute = json["debugmute"];
    appname = String((const char *)json["appname"]);
}

//////////////////////////////////////////////////////////////////////////////
/*
    This is one of the places where you would customize this class to be 
    used with your application specific configuration data.
    
    Another place is in AppCfgData.h
*/
String AppCfgData::getAppName()
{
    return appname;
}

bool AppCfgData::getDebugMute()
{
    return debugmute;
}

