#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "config.h"
#include "functions.h"

void setup() {
#if debug
  Serial.begin(BAUDRATE);
#endif

  //BUILTIN_LED for signaling
  pinMode(BUILTIN_LED, OUTPUT);

  setup_wifi();

  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);

  setup_thermometer();
}

void loop() {
  if (!client.connected()) {
    mqtt_reconnect();
  }
  client.loop();

  now = millis();
  if (now - lastMsg > TEMP_MEAS_INTERVAL) {
    lastMsg = now;
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);
    dtostrf(temperature, 5, 2, msg_to_publish); // (float, size, dec. points, buffer)
#if debug
    Serial.print("Temperature: ");
    Serial.println(msg_to_publish);
#endif
    client.publish(TOPIC_OUT, msg_to_publish);
  }
}
