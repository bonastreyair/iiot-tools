# Communications
## Wifi - Access Point
Code to enable and ESP32 to create its own WiFi network (Access Point - AP) and act as a hub (like WiFi router) for one or more stations. The maximum number of stations that can connect to it is limited to five.

[[Go back]](/communications)
	
### [Code](access_point.ino)
```cpp
#include <WiFi.h>  // Includes the WiFi library

/* Put your desired SSID and Password */
const char *WIFI_SSID = "YOUR_SSID_NAME";
const char *PASSWORD = "YOUR_WIFI_PASSWORD";

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup(){
  Serial.begin(9600);  // Starts the serial communication
  
  // Set desired AP configuration
  WiFi.softAP(WIFI_SSID, PASSWORD);
  WiFi.softAPConfig(local_ip, gateway, subnet);  
  Serial.println("WiFi AP is now active");
}

void loop(){
}
```

### Libraries
* _Wifi_ by [Arduino](https://www.arduino.cc/en/Reference/WiFi) - Installed from the Arduino IDE Library Management
![WiFi_library](../WiFi_library.png)