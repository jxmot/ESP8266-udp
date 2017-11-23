/* ************************************************************************ */
/*
    esp8266-ino.h - support for the associated ino file.

    Stuff that's useful for multiple sketches and helps in keeping the 
    sketch file(s) uncluttered.
*/
#ifndef ESP8266INO_H
#define ESP8266INO_H

#include "AppCfgData.h"
#include "WifiCfgData.h"
#include "SrvCfgData.h"
#include "connectWiFi.h"

#ifdef __cplusplus
extern "C" {
#endif

// support functions - 
extern void setupStart();
extern void setupDone();

extern bool setupApp(const String appCfgFile);
extern bool setupWiFi(const String wifiCfgFile);
extern bool setupServers(const String srvCfgFile);

extern bool toggleLED();

extern void printError(String func, String _errMsg);

extern bool checkDebugMute();

// pointers to configuration data objects - 
extern AppCfgData *a_cfgdat;
extern WifiCfgData *w_cfgdat;
extern SrvCfgData *s_cfgdat;

// pointer to the WiFi connection object -
extern ConnectWiFi *connWiFi;

#ifdef __cplusplus
}
#endif

#endif

