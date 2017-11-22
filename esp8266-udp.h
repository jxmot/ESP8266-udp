/* ************************************************************************ */
/*
    esp8266-udp.h - UDP support for the associated ino file.
*/
#ifndef ESP8266UDP_H
#define ESP8266UDP_H

extern void initUDP();
extern int sendUDP(char *buffer, int len);
extern int recvUDP();

//extern byte *readBuffer;
//extern byte *writeBuffer;
//extern unsigned char *readBuffer;
//extern unsigned char *writeBuffer;
extern unsigned char readBuffer[];
extern unsigned char writeBuffer[];

#endif  // ESP8266UDP_H

