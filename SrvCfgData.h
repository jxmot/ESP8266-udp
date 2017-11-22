/* ************************************************************************ */
/*
    SrvCfgData.h - Intended to provide external server configuration data,
    such as - address and port. 

    NOTE: If the server is providing some type of service that requries 
    an API key or other service specific data then it would also be kept 
    here. Or if too complex for a shared config file then those service
    specific configs could end up in their own file & object.
*/
#ifndef SRVCFGDATA_H
#define SRVCFGDATA_H

#include <IPAddress.h>

#include "ConfigData.h"

// the description of a server
class srvcfg {
    public:
        String label;
        String addr;
        IPAddress ipaddr;
        int recvport;
        int sendport;
};

// to limit memory use only 4 servers can be configured
#define MAX_SRVRS  4
// the last slot is a "end of list" marker.
#define MAX_SRVCFG  MAX_SRVRS + 1

class SrvCfgData : public ConfigData {

    public:
        SrvCfgData(const char *cfgfile, bool muted = false);

    private:
        void parseJSON(std::unique_ptr<char[]>& buf) override;

    //////////////////////////////////////////////////////////////////////////
    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        The other place is in SrvCfgData.cpp
    */
    public:
        bool getServerCfg(String label, srvcfg &cfgout);

    private:
        bool muteDebug;
        static String labels[];
        srvcfg *configs[MAX_SRVCFG];
};

#endif  // SRVCFGDATA_H

