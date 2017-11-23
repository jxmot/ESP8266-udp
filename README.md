# ESP8266-udp

An ESP8266 project that uses UDP to send messages to a server. 

* [Overview](#overview)
* [History](#history)
* [Running the Application](#running-the-application)
    * [A Server for Testing](#a-server-for-testing)
    * [Build and Customize](#build-and-customize)
* [Design Details](#design-details)
* [Code Details](#code-details)
    * [Sketch Source](#sketch-source)
    * [NodeJS Testing Code](#nodejs-testing-code)
* [Future Modifications](#future-modifications)
    * [Submodules](#submodules)
* [Links and References](#links-and-references)
    * [NodeMCU](#nodemcu)
    * [UDP](#udp)
* [Recommended Reading](#recommended-reading)

# Overview

This project demonstrates the use of UDP on an ESP8266 (*NodeMCU v1.0*). It acts as a client and connects with a server. Software components included here come from some of my previous work, such as **[ESP8266-config-data-V2](https://github.com/jxmot/ESP8266-config-data-V2)**.

# History

After I finished a **[RWCL-0516 sensor project](https://github.com/jxmot/ESP8266-RCWL0516)** I decided that I wanted to experiment with UDP and eventually respin the sensor project with UDP capabilities. And this is the result. It was an interesting few days. I had run into problems getting the ESP8266 client side to correctly extract a string from the server's reply. But that was fixed by making sure that the UDP packet and its reply had identically sized payloads.

# Running the Application

## A Server for Testing

You will need a server capable of responding to the UDP packets sent from the sketch. A second ESP8266 could be set up as a server by using one of the many UDP examples found online. A good one is [Arduino/doc/esp8266wifi/udp-examples.rst](https://github.com/esp8266/Arduino/tree/master/doc/esp8266wifi/udp-examples.rst) on Github. Please note that a *Packet Sender* example specific to this project will be provide later.

My preferred test server is NodeJS running a simple script. In my current development set up I use *Visual Studio Code* to run and debug the UDP server code. If you want to go that route I've provided `server-udp.js` which is found in the `nodejs` folder in this repository.

An application called *Packet Sender* is an excellent alternative to a NodeJS server. To see an example on using it with the sketch right-click **[here](PCKTSENDER_EXAMPLE.md)** and open in a new tab or window.

## Build and Customize

In order for the sketch to run on your network and use your UDP server some minor modifications must be made. To see some instructions on modifying it right-click **[here](APPRUN.md)** and open in a new tab or window.

# Design Details

This sketch behaves as a *client* and not as a *server* as shown in most ESP8266 UDP examples. In those examples the ESP8266 *responds* to a UDP packet with a reply. In this sketch it behaves as a client and sends a packet to a server and then it expects a reply from the server.

**CLIENT/SERVER DIAGRAM**

**PROGRAM FLOW**

# Code Details

## Sketch Source

## NodeJS Testing Code

# Future Modifications

Just some things I may experiment with. This section will get updated as I work on them.

## Submodules

## JSON Data

Create functions that can take an *object* and render them as JSON strings. Then send the JSON data to the server and expect a JSON response. The response will then be parsed into an object for use in the application. Possible uses are - 

* Obtaining configuration data.
* Registering a device with a server.
* Sending device/sensor data to a server.

## External Servers

Modifiy the code to allow for *named* servers to be used in the server configuration file. The host names would need to be resolved to IP addresses.

Some level of security may be required. A simple method would be to send the device's MAC in the packet to be used as a *fingerprint*. The server would compare it against a list of known MAC addresses.

# Links and References

## NodeMCU

* [NodeMCU Dev Kit](https://github.com/nodemcu/nodemcu-devkit-v1.0)
* [NodeMCU Documentation](https://nodemcu.readthedocs.io/en/master/)

## UDP

* [Arduino/doc/esp8266wifi/udp-class.rst](https://github.com/esp8266/Arduino/tree/master/doc/esp8266wifi/udp-class.rst) on Github
* [Arduino/doc/esp8266wifi/udp-examples.rst](https://github.com/esp8266/Arduino/tree/master/doc/esp8266wifi/udp-examples.rst) on Github

# Recommended Reading

To fully understand **ArduinoJson** and how to properly determine the appropriate size of the buffer needed for your JSON data I recommend that you read the following - 

* **ESP8266 SPIFFS - Flash File System** documentation, read this first - <http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html>
* **ArduinoJson** documentation, start here - <https://bblanchon.github.io/ArduinoJson/>
* **ArduinoJson Avoiding Pitfalls**, this provides a very good explanation of common pitfalls as related to the ArduinoJson memory model - <https://bblanchon.github.io/ArduinoJson/doc/pitfalls/>
* **ArduinoJson Memory Model**, this explains how the memory model is allocated and information regarding buffer sizes and methods of allocation - <https://bblanchon.github.io/ArduinoJson/doc/memory/>
* **ArduinoJson Assistant** is a tool to aid in determining the correct buffer size based on a sample of the JSON you are working with - <https://bblanchon.github.io/ArduinoJson/assistant/>

