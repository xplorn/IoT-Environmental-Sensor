# IoT-Environmental-Sensor

Simple sensor for temperature, humidity and pressure using WeMos D1 mini ESP8266 and BME280 with Arduino.

## What this is and what this isn't.

Simply, this is a WiFi enabled processor that uses a precise Bosch sensor to measure temperature, humidity and air pressure.  It uses a static IP Address, and connects to a local network using WiFi (2.4GHz).  The sensor is read continuously and outputs via web pages.

This does not connect to any cloud service.  It is meant to be managed within a local environment.  It also does not use DHCP as it is intended to be monitored and data collected along with many like sensors.  

Future designs may make use of DHCP to assign an IP Address if push collection and deep sleep powersaving is added. This will likely end up as a low power design connected to a LiPo battery instead of constant house power.  Making use of MQTT or a similar publish/subscribe protocol with an open smarthome system like OpenHAB to act as an MQTT client is also in the works.

## Current state of things

With multiple sensors, here is an example result of 5 minute data collection from a data collection server and Grafana graphing the results.

## What you need

- breadboard, wires
- WeMos D1 mini
- BME280 with I2C capability
- power supply such as a micro USB cable and wall charger

## Circuit Diagram
