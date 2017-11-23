# ESP8266-udp

An ESP8266 project that uses UDP to send messages to a server. 

* [Overview](#overview)
* [History](#history)
* [Running the Application](#running-the-application)
    * [Requirements](#requirements)
        * [Flash Memory Tool](#flash-memory-tool)
            * [Installation](#installation)
        * [ArduinoJSON](#arduinojson)
    * [Modifications](#odifications)
    * [Server for Testing](#server-for-testing)
    * [Download and Run](#download-and-run)
* [Design Details](#design-details)
* [Code Details](#code-details)
* [Future Modifications](#future-modifications)
    * [Submodules](#submodules)
* [Links and References](#links-and-references)

# Overview

This project demonstrates the use of UDP on an ESP8266 (*NodeMCU v1.0*). It acts as a client and connects with a server. Software components include some of my previous work, such as **[ESP8266-config-data-V2](https://github.com/jxmot/ESP8266-config-data-V2)**.

# History

After I finished a **[RWCL-0516 sensor project](https://github.com/jxmot/ESP8266-RCWL0516)** I decided that I wanted to experiment with UDP and eventually respin the sensor project with UDP capabilities. And this is the result. It was an interesting few days. I had run into problems getting the ESP8266 client side to correctly extract a string from the server's reply.

# Running the Application

## Requirements

You will need the following - 

* ESP8266 - I'm using a NodeMCU 1.0, and it's a 12-E
* Arduino IDE - Installed and made ready for use with the ESP8266
    * In addition to being able to compile code and download for the ESP8266 you **will** need an IDE plug-in for downloading the file(s) to the ESP8266 *flash memory*.
* The [ArduinoJSON](#http://arduinojson.org/) library is used in this application. 

### Flash Memory Tool

I dowloaded the most *recent* version of the plugin by going to <https://github.com/esp8266/arduino-esp8266fs-plugin> and clicking the "releases page" link in the README.

**NOTE :** I am running *Windows 10*. And this file, its instructions and any other information may or may not be influenced by that fact. Where possible I will note any windows specific items.

#### Installation

There are some discrepancies in the available on-line sources in regards to *where* to place the plug-in's `jar` file. In *Windows* I've found that the plugin will work as long as it's in one of two places. They are - 

* `C:\Users\SOME_USER\Documents\Arduino` - you might have to create a `tools` folder here, and then copy the contents of the plugin zip file into it.

**---> OR**

* `C:\Program Files (x86)\Arduino\tools` - copy the contents of the plug-in zip file into this folder.

I've tested the plug-in separately in each of the locations and have had no issues.

### ArduinoJSON

The ArduinoJSON library should be installed via the *library manager* in the Arduino IDE. This application was built and tested with **ArduinoJSON v5.11.0**.

## Modifications

**CONFIG FILES**

## Server for Testing

**NODE or PACKET SENDER**

## Download and Run

# Design Details

**CLIENT/SERVER DIAGRAM**

**PROGRAM FLOW**

# Code Details

# Future Modifications

## Submodules

## JSON Data

Create functions that can take an *object* and render them as JSON strings. Then send the JSON data to the server and expect a JSON response. The response will then be parsed into an object for use in the application. Possible uses are - 

* Obtaining configuration data.
* Registering a device with a server.
* Sending device/sensor data to a server.

## External Servers

Modifiy the code to allow for *named* servers to be used in the server configuration file. The host names would need to be resolved to IP addresses.

# Links and References

