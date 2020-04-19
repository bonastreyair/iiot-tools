# Communications
## MQTT - Publish
How to publish data from an ESP32.

[[Go back]](/communications)

### Hardware
* ESP32

### [Code](publish.ino)
```cpp
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
  Serial.println("Client MQTT published to topic: " + String(newTopic));
}

void publishJson() {
  char buffer[512];  // Create the buffer where we will print the JSON document to publish through MQTT

  // Create JSON document
  StaticJsonDocument<300> jsonDoc;  // A little more than 300 bytes in the stack
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

```

### Functionality explanation

Now that we know what [MQTT](../README.md) is, with this code we can publish either
* Simple string message
```cpp
void publishData() {
  String Data = "Hello there! \n This is a message from my ESP32 with MacAdress:" + String(macAddress) + "\n";
  newTopicStr = String(macAddress) + String("/test");
  const char* newTopic = newTopicStr.c_str();
  const char* PubData = Data.c_str();
  client.publish(newTopic, PubData);
  Serial.println("Client MQTT published to topic: " + String(newTopic));
}
```
* JSON document (serialized)
```cpp
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
  ![PubSubClient](docs/PUB1.png)
  
  This library provides a client for doing simple publish/subscribe messaging with a server that supports MQTT.
   - For more [info](https://pubsubclient.knolleary.net/api.html)
   
  In the code we use:
   - `PubSubClient MQTTClientName(WifiClientName)`: Creates a partially initialised client instance. 
   - `MQTTClientName.setServer(MQTT_BROKER_IP, MQTT_PORT)`:  Sets the server details.
   - `MQTTClientName.connect(ClientID)`: Connects the client. In our case we use the MacAdress as clientID.
   - `MQTTClientName.connected()`: Checks whether the client is connected to the server (false, true).
   - `MQTTClientName.loop()`: This should be called regularly to allow the client to process incoming messages and maintain its connection to the server (false, true).
   - `MQTTClientName.publish(topic, payload)`: Publishes a string message to the specified topic. Both topic and payload have to be a const char.

* **ArduinoJson**

  To install this library we must go to `Tools > Library Manager`, and search for `ArduinoJson` by _Benoit Blanchon_, and click `Install`:
  ![ArduinoJson](docs/PUB2.png)
  
  ArduinoJson is a C++ JSON library for Arduino and IoT (Internet Of Things).
   - For more [info](https://arduinojson.org/v6/api/)
   
  In the code we use:
   - `StaticJsonDocument<300> jsonDoc`: 
    
      `JsonDocument` stores a JSON document in memory. It owns the memory referenced by JsonArray, JsonObject, and JsonVariant.

      `JsonDocument` contains a fixed-size memory pool, with a monotonic allocator. This design allows ArduinoJson to be very efficient but requires some discipline on your side:

      - Because the size is fixed, you need to specify the size when you create the JsonDocument (300 in this case)
      - Because the allocator is monotonic, it cannot release memory when you call JsonObject::remove() for example.
      
   - `jsonDoc["name"] = "value"`: By using this we can add new names nad values on the jsonDoc object.
   - `jsonDoc values = jsonDoc["values"].to<JsonArray>()`: This let us create an array in the jsonDoc object named *values
   - `values.add(27)`: By using this we can add values to the array created.
   
     By using this 3 functions we create a `JSON Document` with and a pair of `key/value` and an `key/array` in it.
       ```
       {
         "device":"ESP32",
         "sensorType":"Temperature",
         "values":[27,29]
       }
       ```
   - `serializeJson(jsonDoc, char buffer)`: This function serializes a `JsonDocument` to create a minified JSON document, i.e. a document without spaces or line break between values. And store it in a *char* for further publish.
   
      `{"device":"ESP32","sensorType":"Temperature","values":[27,29]}`
