/* ************************************************************************ */
/*
    ConfigData.h - This is the base class for all of the configuration 
    classes. 
*/
#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <memory>
#include <WString.h>
#include "FS.h"

#define MAX_FILE_SIZE   1024

class ConfigData {
    
    public:
        ConfigData(const char *cfgfile);
        ~ConfigData();

        bool openCfg(const char *cfgfile);
        bool parseFile();

        int getError(String &s);

    private:
        // every class that derives from this one must provide
        // their own parsing function
        virtual void parseJSON(std::unique_ptr<char[]>& buf);

        File cfgData;

        int error;
        String errmsg;
};

#endif // CONFIGDATA_H

