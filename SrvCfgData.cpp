/* ************************************************************************ */
/*
    SrvCfgData.cpp - Intended to provide external server configuration data,
    such as - address and port. 

    NOTE: If the server is providing some type of service that requries 
    an API key or other service specific data then it would also be kept 
    here. Or if too complex for a shared config file then those service
    specific configs could end up in their own file & object.
*/
#include "SrvCfgData.h"
#include <ArduinoJson.h>

// these are known, but not referenced in the client application
String SrvCfgData::labels[] = {"udp1","udp2","END"};

//////////////////////////////////////////////////////////////////////////////
/*
*/
SrvCfgData::SrvCfgData(const char *cfgfile, bool muted): ConfigData(cfgfile)
{
    muteDebug = muted;

    for(int ix = 0; ix < MAX_SRVCFG; ix++)
    {
        configs[ix] = NULL;
    } 
}

//////////////////////////////////////////////////////////////////////////////
/*
*/
void SrvCfgData::parseJSON(std::unique_ptr<char[]>& buf)
{
    if(!muteDebug)
    {
        Serial.println();
        Serial.println("SrvCfgData parsing JSON - ");
        Serial.println(buf.get());
    }
 
    // https://bblanchon.github.io/ArduinoJson/assistant/
    const size_t bufferSize = JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + 120;
    StaticJsonBuffer<bufferSize> jsonBuffer;

    JsonObject& json = jsonBuffer.parseObject(buf.get());

    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        Another place is in SrvCfgData.h
    */
    for(int ix = 0; labels[ix] != "END"; ix++)
    {
        configs[ix] = new srvcfg();
        configs[ix]->label    = labels[ix];
        configs[ix]->addr     = String((const char *)json[(char *)labels[ix].c_str()]["addr"]);
        configs[ix]->ipaddr.fromString(configs[ix]->addr);
        configs[ix]->recvport = json[(char *)labels[ix].c_str()]["recvport"];
        configs[ix]->sendport = json[(char *)labels[ix].c_str()]["sendport"];
    }
}

//////////////////////////////////////////////////////////////////////////////
/*
    This is one of the places where you would customize this class to be 
    used with your application specific configuration data.
    
    Another place is in SrvCfgData.h
*/
bool SrvCfgData::getServerCfg(String label, srvcfg &cfgout)
{
bool bRet = false;

    for(int ix = 0; (ix < MAX_SRVCFG) && !bRet; ix++)
    {
        if(configs[ix]->label == label)
        {
            cfgout.label    = configs[ix]->label;
            cfgout.addr     = configs[ix]->addr;
            cfgout.ipaddr   = configs[ix]->ipaddr;
            cfgout.recvport = configs[ix]->recvport;
            cfgout.sendport = configs[ix]->sendport;
            bRet = true;
        }
    }
    return bRet;
}


