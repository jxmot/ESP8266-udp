# `esp8266-ino` Functions

A collection of functions to provide a layer of *abstraction* to commonly used resources.

## Setup Functions

* **`void setupStart()`** : Sets the serial baud rate (`DEFAULT_SERIAL_BAUD`), and announces `setup START` on the console.
* **`void setupDone()`** : Announces `setup DONE - No Errors` if setup was successful. Otherwise `No Errors` is replaced with an error message.
-----
* **`bool setupApp(const String appCfgFile)`** : Reads the application configuration file and saves the data in an object pointed to by `AppCfgData *a_cfgdat`. May also perform additional actions depending on the needs of the application.
    * Argument - a `const String` containing the configuration file name + path. For example - `/file.dat`. 
    * Returns **`true`** if successful, **`false`** if not. If an error has occurred an error message will be sent to the serial port. These messages cannot be muted.
-----
* **`bool setupWiFi(const String wifiCfgFile)`** : Reads the WiFi configuration file and saves the data in an object pointed to by `WifiCfgData *w_cfgdat`. The configuration file may contain up to 4 access points. And this function will also attempt to connect to each access point *in sequence* until a connection is made.
    * Argument - a `const String` containing the configuration file name + path. For example - `/file.dat`. 
    * Returns **`true`** if successful, **`false`** if not. If an error has occurred an error message will be sent to the serial port. These messages cannot be muted.
-----
* **`bool setupServers(const String srvCfgFile)`** : Reads the server address configuration file and saves the data in an object pointed to by `SrvCfgData *s_cfgdat`. The configuration file may contain up to 4 servers. 
    * Argument - a `const String` containing the configuration file name + path. For example - `/file.dat`. 
    * Returns **`true`** if successful, **`false`** if not. If an error has occurred an error message will be sent to the serial port. These messages cannot be muted.

## Other Functions

* **`bool checkDebugMute()`** : If the application configuration file has been read and parsed it will return the value of `debugmute` as found in file. If the configuration file has not been read and parsed it will return `true`.
-----
* **`void initLED()`** : Initializes the GPIO pin that is connected to the NodeMCU on-board LED to be an output and writes a HIGH to the pin, this will turn the LED off.

* **`bool toggleLED()`** : If the GPIO pin is not already initialized it will call `initLED()`. It toggles the LED state to be the opposite of it's value when the function was called.
    * Returns **`true`** if the LED was turned ON, and  **`false`** if the LED was turned OFF.
-----
* **`void printError(String func, String _errMsg)`** : Checks the current serial port baud rate and if it doesn't match the default baud rate it will re-initialize the serial port with the default baud rate. Then it sends a message along with a function name to the serial port.
    * Arguments - Requires 2 strings, `func` is the name of the calling function and `_errmsg` is the text message to be sent to the serial port. 

<br>
<br>
&copy; 2017 Jim Motyl

