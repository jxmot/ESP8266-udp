/* ************************************************************************ */
/*
    connectWiFi.h - Assists in making a connection to an access point. If a 
    problem occurs during the connection attempt this class will retry for 
    no more than MAX_ATTEMPTS times.
*/
#ifndef CONNECTWIFI_H
#define CONNECTWIFI_H

// For storing the MAC address raw and
// as ASCII in a character array.
#define MAC_SIZE    6
#define MACSTR_SIZE 18

// Maximum number of times we'll wait and check
// the connection status after a delay.
#define MAX_WAITCONNECTED 5
#define WAITCONNECTED_DELAY 1000

// Maximum number of attempts to make a
// connection to the access point.
#define MAX_ATTEMPTS 5
#define ATTEMPT_DELAY 1000

// Current successful connection information.
typedef struct {
    String  ssid;           // SSID used
    String  passw;          // password used
    String  localIP;        // IP Address obtained
    String  macAddress;     // MAC Address
    uint8_t mac[MAC_SIZE];  // MAC Address (raw)
    int     timeToConnect;  // time in seconds
    int     attempts;       // number of attempts
    bool    isConnected;    // = true, connected
    int     rssi;           // received signal strength
    String  hostname;       // device hostname
} conninfo;

class ConnectWiFi {

    public:
        ConnectWiFi(const char *ssid, const char *passw, conninfo *info = NULL);
        bool GetConnInfo(conninfo *info);
        bool IsConnected();

    private:
        bool connectToAP(const char *ssid, const char *passw);
        void initCurrWiFi(const char *ssid, const char *passw);

        conninfo    currwifi;
};


#endif // CONNECTWIFI_H

