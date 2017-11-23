/* ************************************************************************ */
/*
    esp8266-ino.cpp - support functions for the associated ino file.
*/
#include "AppCfgData.h"
#include "WifiCfgData.h"
#include "SrvCfgData.h"
#include "connectWiFi.h"

#ifdef __cplusplus
extern "C" {
#endif

// if the application configuration is present, and if the debug mute flag is 
// true then mute debug output
#define DEBUG_MUTE ((a_cfgdat != NULL) && a_cfgdat->getDebugMute() ? true : false)

// default serial baud rate, modify as needed
const int DEFAULT_SERIAL_BAUD = 115200;

// functions that are only called from within this module
void initLED();
void printAppCfg();
void printWiFiCfg();
bool connectWiFi(String ssid, String pass);
void printSrvCfg();

// for keeping track of the use of the on-board LED
bool obLEDinUse = false;

// pointers to configuration data objects, after they're 
// created and contain the data they will be available
// through out the run-time of the sketch.
AppCfgData *a_cfgdat = NULL;
WifiCfgData *w_cfgdat = NULL;
SrvCfgData *s_cfgdat = NULL;

// error message string
String errMsg;

// pointer to the WiFi connection object
ConnectWiFi *connWiFi = NULL;

/* ************************************************************************ */
/*
    Print a start up message to the serial port
*/
void setupStart()
{
    Serial.begin(DEFAULT_SERIAL_BAUD);
    Serial.println();
    Serial.println();
    Serial.println("setup START");
    Serial.flush();
}

/*
    Print a start up done message to the serial port
*/
void setupDone()
{
    Serial.flush();
    Serial.println();
    Serial.println("setup DONE - " + (errMsg == "" ? "No Errors" : errMsg));
    Serial.println();
    Serial.flush();

    initLED();
}

void initLED()
{
    // let's blink the LED from within loop()
    pinMode(LED_BUILTIN, OUTPUT);
    delay(10);
    digitalWrite(LED_BUILTIN, HIGH);

    obLEDinUse = true;
}

/*
    Toggle the on-board LED

    Checks to see if the on-board LED pin has been
    configured. If not it will configure it.

    NOTE: The first call to this function will turn on 
    the on-board LED. This behavior can be changed by
    modifying the declaration of ledTogg.

    ledTogg = false - the LED will turn ON with the 
                      first call.

    ledTogg = true  - the LED will turn OFF with the 
                      first call.

    The change in the LED state is also dependent on
    its initialization. That can be changed in setupDone().

*/
bool toggleLED()
{
static bool ledTogg = false;
//static bool ledTogg = true;

    if(obLEDinUse == false) initLED();

    ledTogg = !ledTogg;

    if(ledTogg) digitalWrite(LED_BUILTIN, LOW);
    else digitalWrite(LED_BUILTIN, HIGH);

    return ledTogg;
}

/*
    Print an error message, and change the baud rate if
    necessary.
*/
void printError(String func, String _errMsg)
{
    if(Serial.baudRate() != DEFAULT_SERIAL_BAUD)
    {
        Serial.flush();
        Serial.end();
        Serial.begin(DEFAULT_SERIAL_BAUD);
    }
    Serial.println(func + " ERROR! - " + _errMsg);
}

/*
    Read and parse the application configuration settings, 
    and report any errors.
*/
bool setupApp(const String appCfgFile)
{
String func = String(__func__);
bool bRet = false;

    // get the config data...
    a_cfgdat = new AppCfgData((const char *)appCfgFile.c_str());

    // check for errors
    if(!a_cfgdat->getError(errMsg)) 
    {
        // success, parse the JSON string
        a_cfgdat->parseFile();

        // check for errors
        if(a_cfgdat->getError(errMsg)) printError(func, errMsg);
        else 
        {
            // success, display the config data
            printAppCfg();
            bRet = true;
        }
    } else printError(func, errMsg);

    // return the config-read status, true = success
    return bRet;
}

/*
    Print(to the serial port) the application setting values
*/
void printAppCfg()
{
    if(a_cfgdat != NULL)
    {
        Serial.println("getAppName - " + a_cfgdat->getAppName());
        Serial.println("getDebugMute - " + String(a_cfgdat->getDebugMute() ? "ON" : "OFF"));
        Serial.println();
    }
}

/*
    Read and parse the WiFi configuration settings, and make a
    connection to one of the configured access points. If successful
    then return true, otherwise return false.
*/
bool setupWiFi(const String wifiCfgFile)
{
String func = String(__func__);
bool isconnected = false;

    // get the config data...
    w_cfgdat = new WifiCfgData((const char *)wifiCfgFile.c_str(), DEBUG_MUTE);

    // check for errors
    if(!w_cfgdat->getError(errMsg)) 
    {
        // success, parse the JSON string
        w_cfgdat->parseFile();

        // check for errors
        if(w_cfgdat->getError(errMsg)) printError(func, errMsg);
        else 
        {
            // success, display the config data
            printWiFiCfg();

            // iterate through the configured APs until there's a successful
            // connection or none have occurred.
            int ix = 0;
            for(ix = 0; ix < w_cfgdat->getAPCount() && isconnected == false; ix++)
            {
                // connectWiFi() will retry for a successful connection for
                // specific number of attempts. It will return true if a 
                // connection is made.
                isconnected = connectWiFi(w_cfgdat->getSSID(ix), w_cfgdat->getPASS(ix));
            }

            // success?
            if(!isconnected) 
            {
                // no
                errMsg = "Could not connect to - ";
                for(ix = 0; ix < w_cfgdat->getAPCount(); ix++) errMsg += String("\n    ") + w_cfgdat->getSSID(ix);
                printError(func, errMsg);
            } else errMsg = "";
        }
    } else printError(func, errMsg);

    // return the connection status, true = success
    return isconnected;
}

/*
    Print the WiFi configuration values.
*/
void printWiFiCfg()
{
    if((a_cfgdat != NULL) && !a_cfgdat->getDebugMute())
    {
        Serial.println("getAPCount - " + String(w_cfgdat->getAPCount()));
        Serial.println();

        for(int ix = 0; ix < w_cfgdat->getAPCount(); ix++)
        {
            Serial.println("AP #" + String(ix));
            Serial.println("getSSID - " + w_cfgdat->getSSID(ix));
            Serial.println("getPASS - " + w_cfgdat->getPASS(ix));
            Serial.println();
        }
    }
}

/*
    Get the server address and port configuration values. These
    are typically servers that this application will communicate
    with.
*/
bool setupServers(const String srvCfgFile)
{
String func = String(__func__);
bool bRet = false;

    // get the config data...
    // NOTE: The total quantity of server configs is limited,
    // see the SrvCfgData class for details.
    s_cfgdat = new SrvCfgData((const char *)srvCfgFile.c_str(), DEBUG_MUTE);

    // check for errors
    if(!s_cfgdat->getError(errMsg)) 
    {
        // success, parse the JSON string
        s_cfgdat->parseFile();

        // check for errors
        if(s_cfgdat->getError(errMsg)) printError(func, errMsg);
        else 
        {
            // success, display the config data
            printSrvCfg();
            bRet = true;
        }
    } else printError(func, errMsg);

    // return the config-read status, true = success
    return bRet;
}

/*
    Print the server configuration values
*/
void printSrvCfg()
{
srvcfg cfg;
// NOTE: These strings are used in the configuration file
// to separate the various servers that the application 
// might use. Retrieving the information using a string
// eliminates the need to keep indices in sync between the
// application and the config data.
// 
// To DO: Obtain these strings from a config file, and/or
//        seek a better method.
const String labels[] = {"udp1","udp2","END"};

    if((a_cfgdat != NULL) && !a_cfgdat->getDebugMute())
    {
        for(int ix = 0; labels[ix] != "END"; ix++)
        {
            if(s_cfgdat->getServerCfg(labels[ix], cfg))
            {
                Serial.println("label    = " + cfg.label);
                Serial.println("addr     = " + cfg.addr);
                Serial.println("ipaddr   = " + cfg.ipaddr.toString());
                Serial.println("recvport = " + String(cfg.recvport));
                Serial.println("sendport = " + String(cfg.sendport));
                Serial.println();
            } else Serial.println("not found in cfg - " + labels[ix]);
        }
    }
}

/*
    Connect to an access point with its SSID and password,
    this function will retry for 'N' times if unsuccessful.
    Returns true if connected, otherwise returns false.
*/
bool connectWiFi(String ssid, String pass)
{
conninfo conn;

    // debug stuff
    if((a_cfgdat != NULL) && !a_cfgdat->getDebugMute())
    {
        Serial.println("Attempting connection to - ");
        Serial.println("ssid : " + ssid);
        Serial.println("pass : " + pass);
    }
    // /debug stuff

    // attempt to connect with the specified access point...
    connWiFi = new ConnectWiFi(ssid.c_str(), pass.c_str());

    // debug stuff
    if((a_cfgdat != NULL) && !a_cfgdat->getDebugMute())
    {
        Serial.println("connected? - " + String(connWiFi->IsConnected()? "yes" : "no"));
        Serial.println();

        // connWiFi is global to any code that includes esp8266-ino.h
        // 
        // NOTE: The values are static, and obtained when the connection
        // was successful.
        if(connWiFi->GetConnInfo(&conn)) 
        {
            Serial.println("ip  : " + conn.localIP);
            Serial.println("mac : " + conn.macAddress);
            Serial.println("host: " + conn.hostname);
            Serial.println("Connection Attempt Stats : ");
            Serial.println("attempts = " + String(conn.attempts));
            Serial.println("time     = " + String(conn.timeToConnect));
            Serial.println("rssi     = " + String(conn.rssi) + " dBm");
        }
    }
    // /debug stuff

    return connWiFi->IsConnected();
}

/*
    return the debug mute flag, true = muted

    If the application configuration doesn't exist this function
    will return true (muted)
*/
bool checkDebugMute()
{
    if(a_cfgdat != NULL) return a_cfgdat->getDebugMute();
    return true;
}

#ifdef __cplusplus
}
#endif

