# Communications
## Wifi - Basic
Code to scan the surrounding networks and connect with one.
	
### Code
* [basic.ino](basic.ino)

```cpp
#include <WiFi.h>  // Includes the WiFi library

/* Put your SSID and Password */
const char *WIFI_SSID = "YOUR_SSID_NAME";
const char *PASSWORD = "YOUR_WIFI_PASSWORD";

void setup(){
  Serial.begin(9600);  // Starts the serial communication

  scanNetworks();  // Check nearby networks 
  connectToNetwork();  // Connect the configured network 
  Serial.print("Device IP: ");  // After being connected to a network, our ESP32 should have a IP
  Serial.println(WiFi.localIP());
}

void loop(){
  if (WiFi.status() != WL_CONNECTED) {  // If Wifi disconnected, it tries to reconnect
    Serial.print("Wifi has been disconnected. Trying to reconnect...");
    connectToNetwork();  // Connect the configured network 
  }
  delay(1000);  // Checks every 1000 miliseconds if it has been disconnected
}

/* Additional functions */
void scanNetworks(){
  int numberOfNetworks = WiFi.scanNetworks();
  Serial.println("Number of networks found: " + String(numberOfNetworks));
  for (int i = 0; i < numberOfNetworks; i++) {
    Serial.println("SSID: " + String(WiFi.SSID(i)) + " | RSSI:" + String(WiFi.RSSI(i)));
  }
}

void connectToNetwork(){
  WiFi.begin(WIFI_SSID, PASSWORD);
  Serial.print("Connecting with " + String(WIFI_SSID)); // Print the network which you want to connect  
  while (WiFi.status() != WL_CONNECTED) {  // Connecting effect
    delay(500);
    Serial.print("..");
  }
  Serial.println("connected!");
}
```

### Libraries
* Wifi library by [Arduino](https://www.arduino.cc/) - Installed from the Arduino IDE Library Management
![WiFi_library](../WiFi_library.png)