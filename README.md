# temp_node
IoT node that measures and publishes temperature

Hardware:

The device is based on ESP2866 ESP-1 module.
The temperature measurement is done using digital thermometer DS18B20, whis is connected to GPIO2.
Power supply consists of two AA batteries, which have shown to be sufficient.

Firmware:

The node is using following libraries:
 - ESP8266WiFi.h
 - PubSubClient.h
 - OneWire.h
 - DallasTemperature.h

Main program connects to a home network over wifi, then to an mqtt server and starts to measure and publish temperature.
