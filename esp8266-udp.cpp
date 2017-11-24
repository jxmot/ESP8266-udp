/* ************************************************************************ */
/*
    esp8266-udp.cpp - UDP support for the associated ino file.
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "esp8266-ino.h"
#include "udp-defs.h"

#ifdef __cplusplus
extern "C" {
#endif

// The size (in bytes) of the UDP data that we're expecting 
// to exchange with the server. The +1 is a place holder 
// for a NULL if a string uses the full capacity of the
// buffer.
//
// NOTE: Things seem to work the best when the READ and
// WRITE sizes are the same.
#define UDP_PAYLOAD_SIZE_READ (UDP_PAYLOAD_SIZE + 1)
#define UDP_PAYLOAD_SIZE_WRITE (UDP_PAYLOAD_SIZE + 1)

// read & write buffers
unsigned char readBuffer[UDP_PAYLOAD_SIZE_READ];
unsigned char writeBuffer[UDP_PAYLOAD_SIZE_WRITE];

// Arduino UDP object
WiFiUDP udp;

// a single server configuration
srvcfg udpServer;

/* ************************************************************************ */
/*
    Obtains the UDP configuration data, apply it and do any other necessary
    UDP config steps...
*/
int initUDP()
{
bool success = false;
int iRet = 0;

    // make sure the WiFi is connected...
    if((connWiFi != NULL) && connWiFi->IsConnected())
    {
        // init the UDP...
        s_cfgdat->getServerCfg("udp1", udpServer);
//        s_cfgdat->getServerCfg("udp2", udpServer);
//        if(udp.begin(udpServer.recvport)) success = true;
        if(udp.begin(udpServer.sendport)) success = true;
    }
    if(!checkDebugMute()) Serial.println("initUDP() - success = " + String(success));

    if(success) iRet = UDP_PAYLOAD_SIZE;
    else iRet = 0;

    return iRet;
}

/*
    Send a UDP packet...
*/
int sendUDP(char *payload, int len)
{
int iRet = 0;

    if(!checkDebugMute()) Serial.println("sendUDP() - len = " + String(len));

    // set the entire write buffer contents to 0
    memset(writeBuffer, 0, UDP_PAYLOAD_SIZE_WRITE);

    // if the length of payload is valid then
    // assemble the UDP packet...
    if((len < UDP_PAYLOAD_SIZE_WRITE) && (len > 0))
    {
        // copy the payload into the write buffer
        memcpy(writeBuffer, payload, len);

        // "begin" the UDP packet...
        udp.beginPacket(udpServer.ipaddr, udpServer.sendport);
    
        // write & send the UDP packet...
        iRet = udp.write(writeBuffer, UDP_PAYLOAD_SIZE);

        if(!checkDebugMute()) Serial.println("sendUDP("+String(iRet)+") - sending to " + udpServer.addr + ":" + udpServer.sendport);
    
        // finish & send the packet
        if(udp.endPacket() == 0) iRet = -1;

    } else memset(writeBuffer, 0, UDP_PAYLOAD_SIZE_WRITE);

    return iRet;
}

/*
    If a UDP packet was received then read it and place it
    in the read buffer & return the length of the data read.
*/
int recvUDP()
{
int packetLen;
int readLen = 0;

    // begins processing a packet if one is available
    if(packetLen = udp.parsePacket())
    {
        // clear the read buffer
        memset(readBuffer, 0, UDP_PAYLOAD_SIZE_READ);
        // read the payload
        readLen = udp.read(readBuffer, UDP_PAYLOAD_SIZE);
    }

    if(!checkDebugMute()) Serial.println("recvUDP() - packetLen = " + String(packetLen) + "  readLen = " + readLen);
    return readLen;
}

#ifdef __cplusplus
}
#endif

