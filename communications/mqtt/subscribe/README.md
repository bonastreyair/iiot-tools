# Communications
## MQTT - Subscribe
How to Subscribe to Mqtt topics from an ESP32.

[[Go back]](/communications)

### Hardware
* ESP32

### [Code](subscribe.ino)
```cpp
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
    setMqttSubscriptions();  // Subscribes to configured topics
  }
}
```

### Functionality explanation

Now that we know what [MQTT](../README.md) is, with this code we can subscribe and create a callback function when we recieve message  from different topics

* Subscribe to different topics:
```cpp
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
```
* Define a callback function and define some stuff to do when recieve a message in any topic:
```cpp
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
```

### Libraries
* **Wire** --> Standard in the Arduino libraries folder.

  This library allows you to communicate with I2C / TWI devices.
    - For more [info](https://www.arduino.cc/en/reference/wire)
  
* **Wifi** --> Standard in the Arduino libraries folder.
  
  This library allows an Arduino board to connect to the internet. It can serve as either a server accepting incoming connections or a client making outgoing ones. 
  
    - For more [info](https://www.arduino.cc/en/Reference/WiFi)
  
  In the code we use:
    - `WifiClient WifiClientName`: Creates a client that can connect to to a specified internet IP address and port. (We will use for the MQTT Broker connection)
    - `WiFi.begin(WIFI_SSID, WIFI_PASSWORD)`: Initializes the WiFi library's network settings and provides the current status.
    - `WiFi.status()`: Return the connection status. 
    - `WiFi.macAdress()`: Gets the MAC Address of your WiFi shield
    - `WiFi.localIP()`: Gets the WiFi shield's IP address
 
* **PubSubClient** 

  To install this library we must go to `Tools > Library Manager`, and search for `PubSubClient` by _Nick O'Leary_, and click `Install`:
  ![PubSubClient](../publish/docs/PUB1.png)
  
  This library provides a client for doing simple publish/subscribe messaging with a server that supports MQTT.
   - For more [info](https://pubsubclient.knolleary.net/api.html)
   
  In the code we use:
   - `PubSubClient MQTTClientName(WifiClientName)`: Creates a partially initialised client instance. 
   - `MQTTClientName.setServer(MQTT_BROKER_IP, MQTT_PORT)`:  Sets the server details.
   - `MQTTClientName.connect(ClientID)`: Connects the client. In our case we use the MacAdress as clientID.
   - `MQTTClientName.connected()`: Checks whether the client is connected to the server (false, true).
   - `MQTTClientName.loop()`: This should be called regularly to allow the client to process incoming messages and maintain its connection to the server (false, true).
   - `MQTTClientName.subscribe(topic, QoS)`: Subscribes to messages published to the specified topic.

