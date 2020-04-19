# Communications
## Wifi - Basic
Code to scan the surrounding networks and connect with one.

[[Go back]](/communications)
	
### [Code](basic.ino)
```cpp
#include <WiFi.h>  // Includes the WiFi library

/* Put your SSID and Password */
const char *WIFI_SSID = "YOUR_SSID_NAME";
const char *WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(9600);  // Starts the serial communication

  scanWiFiNetworks();  // Check nearby networks
  connectToWiFiNetwork();  // Connect the configured network
  Serial.print("Device IP: ");  // After being connected to a network, our ESP32 should have a IP
  Serial.println(WiFi.localIP());
}

void loop() {
  checkWiFiConnection();
  delay(1000);  // Checks every 1000 miliseconds if it has been disconnected
}

/* Additional functions */
void scanWiFiNetworks() {
  int numberOfNetworks = WiFi.scanNetworks();
  Serial.println("Number of networks found: " + String(numberOfNetworks));
  for (int i = 0; i < numberOfNetworks; i++) {
    Serial.println("SSID: " + String(WiFi.SSID(i)) + " | RSSI:" + String(WiFi.RSSI(i)));
  }
}

void connectToWiFiNetwork() {
  Serial.print("Connecting with Wi-Fi: " + String(WIFI_SSID));  // Print the network which you want to connect
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print("..");  // Connecting effect
  }
  Serial.print("..connected! (ip: ");  // After being connected to a network, our ESP32 should have a IP
  Serial.println(WiFi.localIP());
}

void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {  // Check WiFi connection
    Serial.println("Connection has been lost with Wi-Fi");
    connectToWiFiNetwork();  // Reconnect WiFi
  }
}
```

### Libraries
* _Wifi_ by [Arduino](https://www.arduino.cc/en/Reference/WiFi) - Installed from the Arduino IDE Library Management
![WiFi_library](../docs/WiFi_library.png)