/* ************************************************************************ */
/*
    esp8266-udp.ino - UDP demonstration for the ESP8266
*/

// If defined then enable "demonstration mode" operations. This includes the
// use of demo-configuration files instead of the ones with sensitive info.
//#define CONFIG_DEMO

// If defined an alternative application configuration file will be used. The 
// intent is to allow compile-time control over whether or not debugging
// information will be sent through the serial connection.
//#define MUTE_DEBUG_OUTPUT

// required include files...
#include "esp8266-ino.h"
#include "esp8266-udp.h"
#include "udp-defs.h"

// The on-board LED is used for indicating the post-setup state. The LED 
// will be toggled using one of two intervals (OFF/ON). The intent is to
// use a slower toggle rate to indicate success, and a faster one to 
// indicate an error during setup.
#define TOGGLE_INTERVAL 1000
#define ERR_TOGGLE_INTERVAL 250

// the default interval for the on-board LED on/off
int toggInterv = TOGGLE_INTERVAL;

// the test data (a string) that we'll send to the server
char *testMsg = "this is a test 1 2 3 4\00";

/* ************************************************************************ */
/*
    Application Set Up
*/
void setup() 
{
    setupStart();

#ifdef MUTE_DEBUG_OUTPUT
    if(setupApp("/_appcfg.dat")) 
    {
#else
    if(setupApp("/appcfg.dat")) 
    {
#endif
#ifdef CONFIG_DEMO
        if(setupWiFi("/wificfg.dat")) 
        {
            if(!setupServers("/servercfg.dat")) toggInterv = ERR_TOGGLE_INTERVAL;
        } else toggInterv = ERR_TOGGLE_INTERVAL;
#else
        // NOTE: The .gitignore in this repo is configured to ignore ALL
        // files that start with an underscore ('_'). This allows for
        // versions of these files that contain "sensitive" information
        // to be ignored by git. The reason that there are two copies of 
        // this code block is to serve as a gentle reminder that there can
        // be additional differences between modes. For example, some config 
        // operations might not be necessary in CONFIG_DEMO.
        if(setupWiFi("/_wificfg.dat")) 
        {
            if(!setupServers("/_servercfg.dat")) toggInterv = ERR_TOGGLE_INTERVAL;
        } else toggInterv = ERR_TOGGLE_INTERVAL;
#endif
    } else  toggInterv = ERR_TOGGLE_INTERVAL;

    // initial setup is complete, wrap up and continue...
    setupDone();

    // if we're not indicating an error the continue with the 
    // initialization of the UDP functionality...
    if(toggInterv == TOGGLE_INTERVAL) 
    {
        if(!initUDP()) 
        {
            printError(String(__func__), "UDP init failed!");
            toggInterv = ERR_TOGGLE_INTERVAL;
        }
    }
}

/*
    Application Execution Loop
*/
void loop() 
{
int sent = 0;
int rcvd = 0;
int ix;

String temp;

    yield();

    // wait now before proceeding...
    delay(toggInterv);

    // toggle the LED and get its current state -
    // true = ON
    // false = OFF
    if(toggleLED()) 
    {
        // the LED will be ON when we send a packet, when the app 
        // was started the call to setupDone() turned it off. so 
        // the first call to toggleLED() will turn the LED on and
        // return `true`.

        // check the error indicator, if no errors then proceed...
        if(toggInterv == TOGGLE_INTERVAL) sent = sendUDP(testMsg, strlen(testMsg));

        // if debug mute is off and we sent something, then announce it...
        if((!checkDebugMute()) && (sent > 0))
        {
            Serial.println();
            Serial.println("loop() - sent = " + String(sent) + "  data = " + String(testMsg));
            Serial.println();
        }
    }
    else 
    {
        // the LED will be OFF when we are waiting to recieve a packet
        if(toggInterv == TOGGLE_INTERVAL) rcvd = recvUDP();

        // if debug mute is off and we received a reply, then announce it...
        if((!checkDebugMute()) && (rcvd > 0))
        {
            Serial.println();
            Serial.println("loop() - rcvd = " + String(rcvd));

            // NOTE: It was assumed that the UDP packet contained a 
            // string of characters. The string could contain anything 
            // (up to udp-defs.h:UDP_PACKET_SIZE bytes in size) even
            // a JSON string. The string MUST be NULL terminated, there's 
            // more info in esp8266-udp.cpp
            temp = String((char *)&readBuffer[0]);

            Serial.println();
            Serial.println("loop() - data = " + temp);
            Serial.println();
            Serial.flush();
        }
    }
}


