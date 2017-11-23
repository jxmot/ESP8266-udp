/* ************************************************************************ */
/*
    esp8266-udp.h - UDP support for the associated ino file.
*/
#ifndef ESP8266UDP_H
#define ESP8266UDP_H

#ifdef __cplusplus
extern "C" {
#endif

extern int initUDP();
extern int sendUDP(char *payload, int len);
extern int recvUDP();

extern unsigned char readBuffer[];
extern unsigned char writeBuffer[];

#ifdef __cplusplus
}
#endif

#endif  // ESP8266UDP_H

