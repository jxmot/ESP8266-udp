* [Running the Application](#running-the-application)
    * [Requirements](#requirements)
        * [ArduinoJSON](#arduinojson)
        * [Flash Memory Tool](#flash-memory-tool)
            * [Installation](#installation)
    * [Download and Run](#download-and-run)
    * [Customization](#customization)
        * [WiFi Configuration](#wifi-configuration)
        * [UDP Server Configuration](#udp-server-configuration)
        * [Muting the Output](#muting-the-output)
        * [Download and Run](#download-and-run)
            * [Success or Failure](#success-or-failure)

# Running the Application

## Requirements

You will need the following - 

* ESP8266 - I'm using a NodeMCU 1.0, and it's a 12-E
* Arduino IDE - Installed and made ready for use with the ESP8266
    * In addition to being able to compile code and download for the ESP8266 you **will** need an IDE plug-in for downloading the file(s) to the ESP8266 *flash memory*.
* The **[ArduinoJSON](#http://arduinojson.org/)** library is used in this application.
* A UDP *server*. This can be at least one of the following - 
    * A running instance of NodeJS. Script files are in the `nodejs` folder in this repository.
    * Use a program like **[Packet Sender](https://packetsender.com/)**.

### ArduinoJSON

The ArduinoJSON library should be installed via the *library manager* in the Arduino IDE. This application was built and tested with **ArduinoJSON v5.11.0**.

### Flash Memory Tool

I dowloaded the most *recent* version of the plugin by going to <https://github.com/esp8266/arduino-esp8266fs-plugin> and clicking the "releases page" link in the README. Download the zip-file and install the plug-in.

**NOTE :** I am running *Windows 10*. And this file, its instructions and any other information may or may not be influenced by that fact. Where possible I will note any windows specific items.

#### Installation

There are some discrepancies in the available on-line sources in regards to *where* to place the plug-in's `jar` file. In *Windows* I've found that the plugin will work as long as it's in one of two places. They are - 

* `C:\Users\SOME_USER\Documents\Arduino` - you might have to create a `tools` folder here, and then copy the contents of the plugin zip file into it.

**---> OR**

* `C:\Program Files (x86)\Arduino\tools` - copy the contents of the plug-in zip file into this folder.

I've tested the plug-in separately in each of the locations and have had no issues.

## Download and Run

**NOTE :** If you're not new to Arduino and/or the ESP8266 you can probably skip this section and jump to [Customization](#customization). This section is meant to make sure everything else is working properly. 
<br>
<br>
<br>
Start with an unmodified version of the code from this repository. Please use the following steps - 

**1**) Run the *Arduino IDE* and open the **ino** file and build & upload it to the ESP8266. **Do not** open the serial monitor.

**2**) Go to the *Tools* menu and find **`Flash Size:`** and choose **'4M (1M SPIFFS)'**.

**3**) Then go to the *Tools* menu and click on **`ESP8266 Sketch Data Upload`**.

Your SPIFFS along with the files it contains will be uploaded to the ESP8266. Be patient, it takes a little while even at 115200b. 

After that has completed open the *serial monitor* and reset the ESP8266. 

To see a serial output example right-click **[here](OUTPUT_EXAMPLE_01.md)** and open in a new tab or window.


## Customization

Let's edit the configuration data and change at least one of the SSID and password combinations to something *usable*.

### WiFi Configuration

**1**) Edit the `wificfg.dat` file, it's found in `/data`

**2**) The contents currently look like this - 

```
{ "apoints":[
{"wifi-ssid":"your ssid-1 here","wifi-pass":"your wifi password-1 here"},
{"wifi-ssid":"your ssid-2 here","wifi-pass":"your wifi password-2 here"}
],"apcount":2}
```

**3**) If you're only going to have one access point in the configuration file, then it should look something like this - 

```
{ "apoints":[
{"wifi-ssid":"your ssid-1 here","wifi-pass":"your wifi password-1 here"}
],"apcount":1}
```

**4**) Save and close the file as **`_wificfg.dat`** (*note the underscore at the beginning of the file name, since this file now contains sensitive information it will be ignored via* `.gitignore` *and cannot be committed*)

### UDP Server Configuration

**1**) Edit the `servercfg.dat` file, it's found in `/data`

**2**) The contents currently look like this - 

```
{
    "udp1":{"addr":"server IP address","recvport":1234,"sendport":1234},
    "udp2":{"addr":"server IP address","recvport":1234,"sendport":1234}
}
```

**3**) Modify the file to look something like this - 

```
{
    "udp1":{"addr":"192.168.0.7","recvport":45321,"sendport":45321},
    "udp2":{"addr":"192.168.0.100","recvport":45321,"sendport":45321}
}
```

**OR** If you have one server - 

```
{
    "udp1":{"addr":"192.168.0.7","recvport":45321,"sendport":45321}
}
```

**4**) Save and close the file as **`_servercfg.dat`** (*note the underscore at the beginning of the file name, since this file now contains sensitive information it will be ignored via* `.gitignore` *and cannot be committed*)

### Muting the Output

In `appcfg.dat` change `debugmute` to `true` and upload the sketch data. Reset and the majority of debug output will be muted. 

### Download and Run

**1**) Run the *Arduino IDE* and go to the *Tools* menu and find **`Flash Size:`** and choose **'4M (1M SPIFFS)'**.

**2**) Open the sketch file in the *Arduino IDE* and find the line containing `#define CONFIG_DEMO`. Comment it out like this - `//#define CONFIG_DEMO`. This change will enable the use of congiguration files where the names start with an underscore. 

**3**) Save the file.

**4**) Verify & upload the sketch to your ESP8266.

**5**) Then go to the *Tools* menu and click on **`ESP8266 Sketch Data Upload`**.

**6**) After the SPIFFS has uploaded you can open the *serial monitor* and reset the ESP8266.

To see a serial output example right-click **[here](OUTPUT_EXAMPLE_02.md)** and open in a new tab or window.

#### Success or Failure

When the WiFi connection is successful the on-board LED will flash with an interval of `TOGGLE_INTERVAL` (*defined in ESP8266-config-data-V2.ino*). However if an error has occurred the LED will flash with an interval of `ERR_TOGGLE_INTERVAL`. Errors are detected and reported to the serial console for - 

* WiFi configuration and connection errors
* Server configuration errors
* UDP Configuration errors


