# ESP8266-udp

An ESP8266 project that uses UDP to send messages to a server. 

* [Overview](#overview)
* [History](#history)
* [Running the Application](#running-the-application)
    * [Requirements](#requirements)
    * [Modifications](#odifications)
* [Code Details](#code-details)
* [Future Modifications](#future-modifications)
    * [Submodules](#submodules)
* [Links and References](#links-and-references)

# Overview

This project demonstrates the use of UDP on an ESP8266 (*NodeMCU v1.0*). It acts as a client and connects with a server. Software components include some of my previous work, such as **[ESP8266-config-data-V2](https://github.com/jxmot/ESP8266-config-data-V2)**.

# History

# Running the Application

## Requirements

## Modifications

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

