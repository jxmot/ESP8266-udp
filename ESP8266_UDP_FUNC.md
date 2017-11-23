# `esp8266-udp` Functions

A collection of functions to provide a layer of *abstraction* to the UDP functions.

## Functions and Global Data

* **`int initUDP()`** : Checks the WifI connection to make sure it's connected. Then it obtains the UDP configuration data for a specified UDP server and initiates listening on a specified port.
    * On success it returns the total number of bytes allowed for a UDP payload. Typically this will be `UDP_PAYLOAD_SIZE` as defined in `udp-defs.h`. On failure it returns `0`.

* **`int sendUDP(char *payload, int len)`** : Sends a UDP packet with data to a server. 
    * Arguments - a pointer to a character string and it's length. 
    * Returns the length of the payload that was sent, or `0` if a error occurred.

* **`int recvUDP()`** : If a UDP packet has been received read and copy it to `readBuffer[]`. 
    * Returns the length of the UDP payload that was copied into `readBuffer[]`. If no packet was received the return will be `0`.
-----
* **`unsigned char readBuffer[]`** : A global buffer to contain payload data from an incoming UDP packet.
    * **NOTE** : The client *should* copy the payload data out of this buffer as soon as it's notified of a received UDP packet. And the client should not rely upon the contents of this buffer beyond that.

* **`unsigned char writeBuffer[]`** : A global buffer that will contain payload data while `sendUDP()` is called.

## Planned Modifications

* Modify the UDP buffers and function(s) *internally* to be of the type `uint8_t`. This would be done to match the buffer argument for `WiFiUDP.wrte()`. The client facing code would use `unsigned char`.