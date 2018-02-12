/* ************************************************************************ */
/*
    MultiCastCfgData.h - Provides the port and any additional info needed to
    send a UDP multi-cast. 
*/
#pragma once

#include <IPAddress.h>
#include "ConfigData.h"

// a multi-cast destination
class mcastcfg {
    public:
        bool enable;
        String addr;
        IPAddress ipaddr;
        int port;
};

class MultiCastCfgData : public ConfigData {

    public:
        MultiCastCfgData(const char *cfgfile, bool muted = false);

    private:
        void parseJSON(std::unique_ptr<char[]>& buf) override;

    //////////////////////////////////////////////////////////////////////////
    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        The other place is in MultiCastCfgData.cpp
    */
    public:
        bool enable;

        bool getCfg(mcastcfg &cfgout);

    private:
        bool muteDebug;

        mcastcfg config;
};

