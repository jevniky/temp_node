// Allow debug ( to hide debug set to 0)
#define debug 1

// Sensors SN
#define DEVICE_SN "TEMP0001"

//Serial comm. baudrate
#define BAUDRATE 9600

// Wifi connection details
#define SSID "***"
#define PASSWORD "***"

//MQTT broker IP address
#define MQTT_BROKER "192.168.0.12"
#define MQTT_PORT 1883
#define RECONNECT_INTERVAL 3000 //MQTT reconnection interval

//Temperature sensor setting
#define ONE_WIRE_BUS 2
#define TEMP_MEAS_INTERVAL 2000
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// arrays to hold device address
DeviceAddress thermometer;

WiFiClient espClient;
char ip_string[16];
PubSubClient client(espClient);
long now = 0; // Time "now" in ms
long lastMsg = 0; // Time when a last message arrived in ms
char msg_to_publish[5]; // Message to be published
float temperature = 0;

#define TOPIC_OUT DEVICE_SN"/tempout"
#define TOPIC_IN DEVICE_SN"/tempin"
#define TOPIC_STATE "clients/"DEVICE_SN"/state"
#define CLIENT_ON "1"
#define CLIENT_OFF "0"
#define MESSAGE_RETAIN_ON TRUE
#define MESSAGE_RETAIN_OFF FALSE
#define WILL_TOPIC "clients/"DEVICE_SN"/state"
#define WILL_QOS 2 // Quality of service
#define WILL_RETAIN MESSAGE_RETAIN_ON // If the will should be retained message
#define WILL_MESSAGE CLIENT_OFF
#define TOPIC_INFO "clients/"DEVICE_SN"/info/ip"
