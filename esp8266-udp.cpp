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

#define UDP_PACKET_SIZE_READ (UDP_PACKET_SIZE + 1)
#define UDP_PACKET_SIZE_WRITE (UDP_PACKET_SIZE + 1)

unsigned char readBuffer[UDP_PACKET_SIZE_READ];
unsigned char writeBuffer[UDP_PACKET_SIZE_WRITE];

WiFiUDP udp;
srvcfg udpServer;

/* ************************************************************************ */
/*
    Obtain the UDP configuration data, apply it and do any other necessary
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

    if(success) iRet = UDP_PACKET_SIZE;
    else iRet = 0;

    return iRet;
}

/*
    
*/
int sendUDP(char *buffer, int len)
{
int iRet = 0;

    if(!checkDebugMute()) Serial.println("sendUDP() - len = " + String(len));

    memset(writeBuffer, 0, UDP_PACKET_SIZE_WRITE);

    // assemble the UDP packet...
    if((len < UDP_PACKET_SIZE_WRITE) && (len > 0))
    {
        memcpy(writeBuffer, buffer, len);

        // "begin" the UDP packet...
        udp.beginPacket(udpServer.ipaddr, udpServer.sendport);
    
        // write & send the UDP packet...
        iRet = udp.write(writeBuffer, UDP_PACKET_SIZE);

        if(!checkDebugMute()) Serial.println("sendUDP("+String(iRet)+") - sending to " + udpServer.addr + ":" + udpServer.sendport);
    
        if(udp.endPacket() == 0) iRet = -1;

    } else memset(writeBuffer, 0, UDP_PACKET_SIZE_WRITE);

    return iRet;
}

/*
    
*/
int recvUDP()
{
int packetLen;
int readLen = 0;

    if(packetLen = udp.parsePacket())
    {
        memset(readBuffer, 0, UDP_PACKET_SIZE_READ);
        readLen = udp.read(readBuffer, UDP_PACKET_SIZE);
    }

    if(!checkDebugMute()) Serial.println("recvUDP() - packetLen = " + String(packetLen) + "  readLen = " + readLen);
    return readLen;
}

#ifdef __cplusplus
}
#endif

