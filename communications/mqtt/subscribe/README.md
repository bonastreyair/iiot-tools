# Communications
## MQTT - Subscribe
How to Subscribe to MQTT topics from an ESP32.

[[Go back]](/communications/mqtt)

### Hardware
- ESP32

### [Code](subscribe.ino)
```cpp
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>  // https://github.com/knolleary/pubsubclient

// Define new subscription topics here
#define COMMAND_TOPIC  "cmd"
#define TEST_TOPIC     "test"

// Replace the next variables with your Wi-Fi SSID/Password
const char *WIFI_SSID = "YOUR_SSID_NAME";
const char *WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
char macAddress[18];

// Add MQTT Broker settings
const char *MQTT_BROKER_IP = "BROKER_IP";
const int MQTT_PORT = 1883;
const bool RETAINED = true;
const int QoS = 0;  // Quality of Service for the subscriptions

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(9600);  // Starts the serial communication
  Serial.println("");

  mqttClient.setServer(MQTT_BROKER_IP, MQTT_PORT);  // Connect the configured mqtt broker
  mqttClient.setCallback(callback);  // Prepare what to do when a message is recieved

  connectToWiFiNetwork();  // Connects to the configured network
  connectToMqttBroker();  // Connects to the configured mqtt broker
  setSubscriptions();  // Subscribe defined topics
}

void loop() {
  checkConnections();  // We check the connection every time
}

/* Additional functions */
void setSubscriptions() {
  subscribe(COMMAND_TOPIC);
  subscribe(TEST_TOPIC);
}

void subscribe(char* newTopic) {
  const String topicStr = createTopic(newTopic);
  const char* topic = topicStr.c_str();
  mqttClient.subscribe(topic, QoS);
  Serial.println("Client MQTT subscribed to topic: " + topicStr + " (QoS:" + String(QoS) + ")");
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Register all subscription topics
  static const String cmdTopicStr = createTopic(COMMAND_TOPIC);
  static const String testTopicStr = createTopic(TEST_TOPIC);

  String msg = unwrapMessage(payload, length);
  Serial.println(" => " + String(topic) + ": " + msg);

  // What to do in each topic case?
  if (String(topic) == cmdTopicStr) {
    // Do some command
  } else if (String(topic) == testTopicStr) {
    // Do some other stuff
  } else {
    Serial.println("[WARN] - '" + String(topic) + "' topic was correctly subscribed but not defined in the callback function");
  }
}

String unwrapMessage(byte* message, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {  // Unwraps the string message
    msg += (char)message[i];
  }
  return msg;
}

String createTopic(char* topic) {
  String topicStr = String(macAddress) + "/" + topic;
  return topicStr;
}

void connectToWiFiNetwork() {
  Serial.print("Connecting with Wi-Fi: " + String(WIFI_SSID));  // Print the network which you want to connect
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print("..");  // Connecting effect
  }
  Serial.print("..connected!  (ip: ");  // After being connected to a network, our ESP32 should have a IP
  Serial.print(WiFi.localIP());
  Serial.println(")");
  String macAddressStr = WiFi.macAddress().c_str();
  strcpy(macAddress, macAddressStr.c_str());
}

void connectToMqttBroker() {
  Serial.print("Connecting with MQTT Broker: " + String(MQTT_BROKER_IP));  // Print the broker which you want to connect
  mqttClient.connect(macAddress);  // Using unique mac address from ESP32
  while (!mqttClient.connected()) {
    delay(500); Serial.print("..");  // Connecting effect
    mqttClient.connect(macAddress);  // Using unique mac address from ESP32
  }
  Serial.println("..connected! (ClientID: " + String(macAddress) + ")");
}

void checkConnections() {
  if (mqttClient.connected()) {
    mqttClient.loop();
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
```

### Functionality explanation
Now that we know what [MQTT](../README.md) is, with this code we can subscribe and create a callback function when we recieve message from different topics

#### How to subscribe to a topics? 
```cpp
void subscribe(char* newTopic) {
  const String topicStr = createTopic(newTopic);
  const char* topic = topicStr.c_str();
  mqttClient.subscribe(topic, QoS);
  Serial.println("Client MQTT subscribed to topic: " + topicStr + " (QoS:" + String(QoS) + ")");
}

String createTopic(char* topic) {
  String topicStr = String(macAddress) + "/" + topic;
  return topicStr;
}
```

#### Where do the subscriptions arrive?
```cpp
void callback(char* topic, byte* payload, unsigned int length) {
  // Register all subscription topics
  static const String cmdTopicStr = createTopic(COMMAND_TOPIC);
  static const String testTopicStr = createTopic(TEST_TOPIC);

  String msg = unwrapMessage(payload, length);
  Serial.println(" => " + String(topic) + ": " + msg);

  // What to do in each topic case?
  if (String(topic) == cmdTopicStr) {
    // Do some command
  } else if (String(topic) == testTopicStr) {
    // Do some other stuff
  } else {
    Serial.println("[WARN] - '" + String(topic) + "' topic was correctly subscribed but not defined in the callback function");
  }
}

String unwrapMessage(byte* message, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {  // Unwraps the string message
    msg += (char)message[i];
  }
  return msg;
}
```

### Libraries
- [_Wire_](https://www.arduino.cc/en/reference/wire) by Arduino - Preinstalled with the Arduino IDE
  
  This library allows you to communicate with I2C / TWI devices.

- [_Wifi_](https://www.arduino.cc/en/Reference/WiFi) by Arduino - Installed from the Arduino IDE Library Management

  ![WiFi_library](../docs/WiFi_library.png)
 
  This library allows an Arduino board to connect to a wifi router. It can be used as either a server accepting incoming connections or as a client. Some of the functions we use are:
  - `WifiClient wifiClient`: Creates a client that can connect to to a specified internet IP address and port. (We will use for the MQTT Broker connection)
  - `WiFi.begin(WIFI_SSID, WIFI_PASSWORD)`: Initializes the WiFi library's network settings and provides the current status
  - `WiFi.status()`: Return the connection status
  - `WiFi.macAdress()`: Gets the MAC Address of your WiFi shield
  - `WiFi.localIP()`: Gets the WiFi shield's IP address
 
- [_PubSubClient_](https://pubsubclient.knolleary.net/api.html) by Nick O'Leary - Installed from the Arduino IDE Library

  ![PubSubClient](../publish/docs/PUB1.png)
  
  This library provides a client for doing simple publish/subscribe messaging with a server that supports MQTT. Some of the functions we use are:
  - `PubSubClient mqttClient(wifiClient)`: Creates a partially initialised client instance.
  - `mqttClient.setServer(MQTT_BROKER_IP, MQTT_PORT)`:  Sets the server details
  - `mqttClient.connect(clientID)`: Connects the client. In our case we use the macAdress as the clientID
  - `mqttClient.connected()`: Checks whether the client is connected to the server (`false`, `true`)
  - `mqttClient.loop()`: This should be called regularly to allow the client to process incoming messages and maintain its connection to the server (`false`, `true`)
  - `mqttClient.subscribe(topic, QoS)`: Subscribes to messages published to the specified topic with a Quality of Service

[[Go back]](/communications/mqtt)
