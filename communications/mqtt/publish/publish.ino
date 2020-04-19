#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Replace the next variables with your Wi-Fi SSID/Password
const char* WIFI_SSID = "WIFI_SSID";
const char* WIFI_PASSWORD = "WIFI_PASSWORD";
char macAddress[18];

// Add MQTT Broker settings
const char* MQTT_BROKER_IP = "BROKER_IP";
const int MQTT_PORT = 1883;
const bool RETAINED = true;
const int QoS = 0;  // Quality of Service for the subscriptions

WiFiClient espClient;
PubSubClient client(espClient);

// Topic Variables
String jsonTopicStr;
String newTopicStr;

int lastPublishTime = millis();  // Initialize time

void setup() {
  Serial.begin(9600);  // Starts the serial communication
  Serial.println("");

  client.setServer(MQTT_BROKER_IP, MQTT_PORT);  // Connect the configured mqtt broker

  connectToWiFiNetwork();  // Connects to the configured network
  connectToMqttBroker();  // Connects to the configured mqtt broker
}

void loop() {
  checkConnections();  // We check the connection every time

  int nowTime = millis();
  if (nowTime - lastPublishTime >= 5000) { // We only publish information every 5 seconds
    publishData();  // Publishes to counter topic
    publishJson();  // Subscribes to json topic
    lastPublishTime = nowTime;
  }
}

/* Additional functions */
void publishData() {
  String Data = "Hello there! \n This is a message from my ESP32 with MacAdress:" + String(macAddress) + "\n";
  newTopicStr = String(macAddress) + String("/test");
  const char* newTopic = newTopicStr.c_str();
  const char* PubData = Data.c_str();
  client.publish(newTopic, PubData);
  Serial.println("Client MQTT published to topic: " + String(newTopic) + " (QoS:" + String(QoS) + ")");
}

void publishJson() {
  char buffer[512];  // Create the buffer where we will print the JSON document to publish through MQTT

  // Create JSON document
  StaticJsonDocument<300> jsonDoc; // A little more than 300 bytes in the stack
  jsonDoc["device"] = "ESP32";  // Add names and values to the JSON document
  jsonDoc["sensorType"] = "Temperature";
  JsonArray values = jsonDoc["values"].to<JsonArray>();  // Or we can add an array to the string "values"

  values.add(27);  // Inside the array we can add new values to "values"
  values.add(29);

  serializeJson(jsonDoc, buffer);  // Serialize the JSON document to a buffer in order to publish it

  jsonTopicStr = String(macAddress) + String("/json");
  const char* jsonTopic = jsonTopicStr.c_str();
  client.publish(jsonTopic, buffer);
  Serial.println("Client MQTT published to topic: " + String(jsonTopic));
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
  }
}
