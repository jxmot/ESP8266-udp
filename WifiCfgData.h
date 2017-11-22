/* ************************************************************************ */
/*
    WifiCfgData.h - Intended to provide WiFi configuration data, this
    will be things such as - 

        1) SSID
        2) password

*/
#ifndef WIFICFGDATA_H
#define WIFICFGDATA_H

#include "ConfigData.h"

// due to limited memory there will be only up to
// 4 access points allowed in the config file
#define MAX_APOINTS 4

// An access point - 
class apoint {
    public:
        String ssid;
        String pass;
};

class WifiCfgData : public ConfigData {

    public:
        WifiCfgData(const char *cfgfile, bool muted = false);

    private:
        void parseJSON(std::unique_ptr<char[]>& buf) override;

    //////////////////////////////////////////////////////////////////////////
    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        The other place is in WifiCfgData.cpp
    */
    public:
        int getAPCount();

        char *getSSID(int apidx = 0);
        String getSSIDString(int apidx = 0);
        
        char *getPASS(int apidx = 0);
        String getPASSString(int apidx = 0);
        
    private:
        bool muteDebug;

        int apcount;
        apoint aps[MAX_APOINTS];
};

#endif  // WIFICFGDATA_H

