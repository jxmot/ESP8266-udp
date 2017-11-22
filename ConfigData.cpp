/* ************************************************************************ */
/*
    ConfigData.cpp - This is the base class for all of the configuration 
    classes. 
    
    This class makes use of SPIFFS, it expects the configuration file to be
    present. The file must properly formatted as JSON.
*/
#include <ArduinoJson.h>

#include "ConfigData.h"

//////////////////////////////////////////////////////////////////////////////
// Sources of information that I found useful when creating this code -
// 
// http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html
//
// https://github.com/esp8266/arduino-esp8266fs-plugin
//
// http://www.instructables.com/id/Using-ESP8266-SPIFFS/
//
//////////////////////////////////////////////////////////////////////////////
/*
    
*/
ConfigData::ConfigData(const char *cfgfile) : cfgData(NULL), error(0), errmsg("")
{
    openCfg(cfgfile);
}

ConfigData::~ConfigData()
{
    if(cfgData != NULL) cfgData.close();
    SPIFFS.end();
}

bool ConfigData::openCfg(const char *cfgfile)
{
bool bRet = false;

    // important info - 
    //      https://github.com/esp8266/Arduino/blob/master/doc/filesystem.rst
    SPIFFS.begin();

    // if there's the possibility that a file has already been
    // opened then close it now.
    if(cfgData != NULL) cfgData.close();

    // open the file and check for success...
    if(cfgData = SPIFFS.open(cfgfile, "r")) bRet = true;
    else 
    {
        cfgData = File(NULL);

        // it didn't open, note the likely error.
        error = -1;
        errmsg = "The configuration data file [" + String(cfgfile) + "] doesn't exist.";
    }
    return bRet;
}

bool ConfigData::parseFile()
{
bool bRet = false;

    if (!cfgData) 
    {
        // it didn't open, note the likely error.
        error = -2;
        errmsg = "The configuration data file is not open.";
    }
    else
    {
        // it's best to keep the size of the JSON configuration
        // files reasonably small. 
        if(cfgData.size() > MAX_FILE_SIZE) 
        {
            cfgData.close();

            error = -3;
            errmsg = "Configuration file size is too large";
        }
        else
        {
            // Allocate a buffer to store contents of the file.
            std::unique_ptr<char[]> buf(new char[cfgData.size()]);

            // https://bblanchon.github.io/ArduinoJson/
            // 
            // We don't use String here because ArduinoJson library requires the input
            // buffer to be mutable. If you don't use ArduinoJson, you may as well
            // use configFile.readString instead.
            cfgData.readBytes(buf.get(), cfgData.size());
            //Serial.println(cfgData.size());
            //Serial.println(buf.get());
            parseJSON(buf);
            error = 0;
            bRet = true;
        }
    }
    return(bRet);
}

int ConfigData::getError(String &s) 
{
    s = errmsg;
    return error;
}

void ConfigData::parseJSON(std::unique_ptr<char[]>& buf)
{
    // NOTE: Virtual function, derived classes must
    // implement their own parseJSON().
}

