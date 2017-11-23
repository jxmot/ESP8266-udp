/* ************************************************************************ */
/*
    WifiCfgData.cpp - Intended to provide Wifi configuration data, this
    will be things such as - 

        1) SSID
        2) password

*/
#include "WifiCfgData.h"
#include <ArduinoJson.h>

//////////////////////////////////////////////////////////////////////////////
/*
    Read the configuration file and optionally mute debug console output
*/
WifiCfgData::WifiCfgData(const char *cfgfile, bool muted): ConfigData(cfgfile)
{
    apcount = 0; 
    muteDebug = muted;
}

//////////////////////////////////////////////////////////////////////////////
/*
    Parse the JSON string into an object specific to this class
*/
void WifiCfgData::parseJSON(std::unique_ptr<char[]>& buf)
{
    if(!muteDebug)
    {
        Serial.println();
        Serial.println("WifiCfgData parsing JSON - ");
        Serial.println(buf.get());
        Serial.println();
    }
 
    // For getting the size correct, use the following to calculate
    // how much is requried for a given bit of JSON data - 
    //
    //      https://bblanchon.github.io/ArduinoJson/assistant/
    const size_t bufferSize = JSON_ARRAY_SIZE(2) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 180;
    StaticJsonBuffer<bufferSize> jsonBuffer;

    JsonObject& json = jsonBuffer.parseObject(buf.get());

    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        Another place is in WifiCfgData.h
    */
    apcount = json["apcount"];

    for(int ix = 0; ix < MAX_APOINTS; ix++) {
        aps[ix].ssid = "";
        aps[ix].pass = "";
    }

    if(apcount <= MAX_APOINTS) {
        for(int ix = 0; ix < apcount; ix++) {
            aps[ix].ssid = String((const char*)json["apoints"][ix]["ssid"]);
            aps[ix].pass = String((const char*)json["apoints"][ix]["pass"]);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
/*
    This is one of the places where you would customize this class to be 
    used with your application specific configuration data.
    
    Another place is in WifiCfgData.h
*/
int WifiCfgData::getAPCount()
{
    return apcount;
}

String WifiCfgData::getSSID(int apidx)
{
    if(apidx < apcount) return aps[apidx].ssid;
    else return String("");
}

String WifiCfgData::getPASS(int apidx)
{
    if(apidx < apcount) return aps[apidx].pass;
    else return String("");
}
