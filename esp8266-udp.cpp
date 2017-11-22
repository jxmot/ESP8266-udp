/* ************************************************************************ */
/*
    esp8266-udp.cpp - UDP support for the associated ino file.
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "esp8266-ino.h"

#define UDP_PACKET_SIZE_READ 75
#define UDP_PACKET_SIZE_WRITE 75

//byte readBuffer[UDP_PACKET_SIZE_READ];
//byte writeBuffer[UDP_PACKET_SIZE_WRITE];
unsigned char readBuffer[UDP_PACKET_SIZE_READ];
//unsigned char readBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
unsigned char writeBuffer[UDP_PACKET_SIZE_WRITE];
//byte readBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
//byte writeBuffer[UDP_PACKET_SIZE_WRITE];

WiFiUDP udp;
srvcfg udpServer;

bool initUDP()
{
bool bRet = false;

    // make sure the WiFi is connected...
    if((connWiFi != NULL) && connWiFi->IsConnected())
    {
        // init the UDP...
        s_cfgdat->getServerCfg("udp1", udpServer);
//        s_cfgdat->getServerCfg("udp2", udpServer);
//        if(udp.begin(udpServer.recvport)) bRet = true;
        if(udp.begin(udpServer.sendport)) bRet = true;
    }
    if(!checkDebugMute()) Serial.println("initUDP() - bRet = " + String(bRet));
    return bRet;
}

int sendUDP(char *buffer, int len)
{
int iRet = 0;

    if(!checkDebugMute()) Serial.println("sendUDP() - len = " + String(len));

    memset(writeBuffer, 0, UDP_PACKET_SIZE_WRITE);

    // assemble the UDP packet...
    if((len <= UDP_PACKET_SIZE_WRITE) && (len > 0))
    {
        memcpy(writeBuffer, buffer, len);

        // "begin" the UDP packet...
        udp.beginPacket(udpServer.ipaddr, udpServer.sendport);
    
        // write & send the UDP packet...
        iRet = udp.write(writeBuffer, UDP_PACKET_SIZE_WRITE);

        if(!checkDebugMute()) Serial.println("sendUDP("+String(iRet)+") - sending to " + udpServer.addr + ":" + udpServer.sendport);
    
        if(udp.endPacket() == 0) iRet = -1;

    } else memset(writeBuffer, 0, UDP_PACKET_SIZE_WRITE);

    return iRet;
}

int recvUDP()
{
int packetLen;
int readLen = 0;

    if(packetLen = udp.parsePacket())
    {
        memset(readBuffer, 0, UDP_PACKET_SIZE_READ);
        readLen = udp.read(readBuffer, UDP_PACKET_SIZE_READ);
    }

    if(!checkDebugMute()) Serial.println("recvUDP() - packetLen = " + String(packetLen) + "  readLen = " + readLen);
    return readLen;
}


