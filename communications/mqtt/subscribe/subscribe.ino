#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Replace the next variables with your Wi-Fi SSID/Password
const char* WIFI_SSID = "YOUR_SSID_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
char macAddress[18];

// Add MQTT Broker settings
const char* MQTT_BROKER_IP = "BROKER_IP";
const int MQTT_PORT = 1883;
const bool RETAINED = true;
const int QoS = 0;  // Quality of Service for the subscriptions

WiFiClient espClient;
PubSubClient client(espClient);

// Topic Variables
String cmdTopicStr;
String newTopicStr;

void setup() {
  Serial.begin(9600);  // Starts the serial communication
  Serial.println("");

  client.setServer(MQTT_BROKER_IP, MQTT_PORT);  // Connect the configured mqtt broker
  client.setCallback(callback);  // Prepare what to do when a message is recieved

  connectToWiFiNetwork();  // Connects to the configured network
  connectToMqttBroker();  // Connects to the configured mqtt broker
  setSubscriptions();  // Subscribes to configured topics
}

void loop() {
  checkConnections();
}

/* Additional functions */
void setSubscriptions() {
  cmdTopicStr = String(macAddress) + String("/cmd");
  const char* cmdTopic = cmdTopicStr.c_str();
  client.subscribe(cmdTopic, QoS);
  Serial.println("Client MQTT subscribed to topic: " + cmdTopicStr + " (QoS:" + String(QoS) + ")");

  newTopicStr = String(macAddress) + String("/test");
  const char* newTopic = newTopicStr.c_str();
  client.subscribe(newTopic, QoS);
  Serial.println("Client MQTT subscribed to topic: " + newTopicStr + " (QoS:" + String(QoS) + ")");
}

void callback(char* topic, byte* message, unsigned int length) {
  String msg = unwrap(message, length);
  Serial.println(String(topic) + ": " + msg);

  if (String(topic) == cmdTopicStr) {
    // Do some command
  } else if (String(topic) == newTopicStr) {
    // Do some other stuff
  } else {
    Serial.println("[WARN] - '" + String(topic) + "' topic was correctly subscribed but not defined in the callback function");
  }
}

String unwrap(byte* message, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {  // Unwraps the string message
    msg += (char)message[i];
  }
  return msg;
}

void connectToWiFiNetwork() {
  Serial.print("Connecting with Wi-Fi: " + String(WIFI_SSID));  // Print the network which you want to connect
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print("..");  // Connecting effect
  }
  Serial.print("..connected! (ip: ");  // After being connected to a network, our ESP32 should have a IP
  Serial.println(WiFi.localIP());
  String macAddressStr = WiFi.macAddress().c_str();
  strcpy(macAddress, macAddressStr.c_str());
}


void connectToMqttBroker() {
  Serial.print("Connecting with MQTT Broker: " + String(MQTT_BROKER_IP));  // Print the broker which you want to connect
  client.connect(macAddress);  // Using unique mac address from ESP32
  while (!client.connected()) {
    delay(500); Serial.print("..");  // Connecting effect
    client.connect(macAddress);  // Using unique mac address from ESP32
  }
  Serial.println("..connected! (ClientID: " + String(macAddress) + ")");
}

void checkConnections() {
  if (client.connected()) {
    client.loop();
  } else {  // Try to reconnect
    Serial.println("Connection has been lost with MQTT Broker");
    if (WiFi.status() != WL_CONNECTED) {  // Check wifi connection
      Serial.println("Connection has been lost with Wi-Fi");
      connectToWiFiNetwork();  // Reconnect Wifi
    }
    connectToMqttBroker();  // Reconnect Server MQTT Broker
    setSubscriptions();  // Subscribes to configured topics
  }
}
