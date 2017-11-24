# Download and Run - Output Example #2

You should now see something *like this* - 

```
setup START

AppCfgData parsing JSON - 
{"appname":"My Application","debugmute":false}

getAppName - My Application
getDebugMute - OFF


WifiCfgData parsing JSON - 
{ "apoints":[
{"wifi-ssid":"usable_SSID_1","wifi-pass":"wifipassw1"},
{"wifi-ssid":"usable_SSID_2","wifi-pass":"wifipassw2"}
],"apcount":2}

getAPCount - 2

AP #0
getSSID - usable_SSID_1
getPASS - wifipassw1

AP #1
getSSID - usable_SSID_2
getPASS - wifipassw2

Attempting connection to - 
ssid : usable_SSID_2
pass : wifipassw2
connected? - yes

ip  : 192.168.0.14
mac : 60:01:00:00:00:02
host: ESP_000002
Connection Attempt Stats : 
attempts = 1
time     = 3
rssi     = -37 dBm

SrvCfgData parsing JSON - 
{
    "http":{"addr":"192.168.0.26","port":80},
    "devapi":{"addr":"192.168.0.26","port":4843},
    "websock":{"addr":"192.168.0.26","port":8080}
}

label = http
addr  = 192.168.0.26
port  = 80

label = devapi
addr  = 192.168.0.26
port  = 4843

label = websock
addr  = 192.168.0.26
port  = 8080


setup DONE - No Errors
```

Where `usable_SSID_1`, `usable_SSID_2` and `wifipassw1`, `wifipassw2` are the values you edited in the **`/data/_wificfg.dat`** file.

<br>
<br>
&copy; 2017 James Motyl

