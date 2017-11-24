# Download and Run - Output Example #1

You should see this in the serial monitor - 

```
setup START

AppCfgData parsing JSON - 
{"appname":"My Application","debugmute":false}

getAppName - My Application
getDebugMute - OFF


WifiCfgData parsing JSON - 
{ "apoints":[
{"ssid":"your ssid-1 here","pass":"your wifi password-1 here"},
{"ssid":"your ssid-2 here","pass":"your wifi password-2 here"}
],"apcount":2}

getAPCount - 2

AP #0
getSSID - your ssid-1 here
getPASS - your wifi password-1 here

AP #1
getSSID - your ssid-2 here
getPASS - your wifi password-2 here

Attempting connection to - 
ssid : your ssid-1 here
pass : your wifi password-1 here
connected? - no

Attempting connection to - 
ssid : your ssid-2 here
pass : your wifi password-2 here
connected? - no

setupWiFi ERROR! - Could not connect to - 
    your ssid-1 here
    your ssid-2 here

setup DONE - Could not connect to - 
    your ssid-1 here
    your ssid-2 here

```

Since all attempts failed the on-board LED will flash with an interval of `ERR_TOGGLE_INTERVAL` (*defined in ESP8266-udp.ino*).

<br>
<br>
&copy; 2017 James Motyl

