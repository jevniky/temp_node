void setup_wifi() {
  // We start by connecting to a WiFi network
#if debug
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);
#endif

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    digitalWrite(BUILTIN_LED,!digitalRead(BUILTIN_LED));
    #if debug
    Serial.print(".");
    #endif
  }

  IPAddress ip_addr = WiFi.localIP();
  sprintf(ip_string, "%d.%d.%d.%d", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);

#if debug
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
#endif
}

void callback(char* topic, byte* payload, unsigned int length) {
#if debug
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
#endif
}

void mqtt_reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
#if debug
    Serial.print("Attempting MQTT connection...");
#endif
    // Attempt to connect
    // if (client.connect(DEVICE_SN)) {
    if (client.connect(DEVICE_SN, WILL_TOPIC, WILL_QOS, WILL_RETAIN, WILL_MESSAGE)) {
#if debug
      Serial.println("connected");
#endif
      // Once connected, publish an announcement...
      client.publish(TOPIC_STATE, CLIENT_ON, MESSAGE_RETAIN_ON);
      client.publish(TOPIC_INFO, ip_string, MESSAGE_RETAIN_ON);
      // ... and resubscribe
      client.subscribe(TOPIC_IN);
    } else {
#if debug
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
#endif
      // Wait 5 seconds before retrying
      delay(RECONNECT_INTERVAL);
    }
  }
}

void setup_thermometer(){
  sensors.begin();
  sensors.getAddress(thermometer, 0);
  sensors.setResolution(thermometer, 12);
}
