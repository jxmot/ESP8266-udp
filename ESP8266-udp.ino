

#include "esp8266-ino.h"
#include "esp8266-udp.h"

#define TOGGLE_INTERVAL 1000
#define ERR_TOGGLE_INTERVAL 250
int toggInterv = TOGGLE_INTERVAL;

const char *testMsg = "this is a test 1 2 3 4\00";

/*
    Application Set Up
*/
void setup() 
{
    setupStart();

    if(setupApp("/appcfg.dat"))
        if(setupWiFi("/wificfg.dat")) setupServers("/servercfg.dat");
        else toggInterv = ERR_TOGGLE_INTERVAL;

    setupDone();

    if(toggInterv == TOGGLE_INTERVAL) initUDP();
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

    delay(toggInterv);

    if(toggleLED()) 
    {
        // the LED will be ON when we send a packet, when the app 
        // was started the call to setupDone() turned it off. so 
        // the first call to toggleLED() will turn the LED on.

        if(toggInterv == TOGGLE_INTERVAL) sent = sendUDP(testMsg, strlen(testMsg));

        if((!checkDebugMute()) && (sent > 0))
        {
            Serial.println();
            Serial.println("loop() - sent = " + String(sent) + "  data = " + String(testMsg));
            Serial.println();
        }
    }
    else 
    {
        // the LED will be ON when we are waiting to recieve a packet
        if(toggInterv == TOGGLE_INTERVAL) rcvd = recvUDP();

        if((!checkDebugMute()) && (rcvd > 0))
        {
            Serial.println();
            Serial.println("loop() - rcvd = " + String(rcvd));

            temp = String((char *)&readBuffer[0]);

            Serial.println();
            Serial.println("loop() - data = " + temp);
            Serial.println();
            Serial.flush();
        }
    }
}


