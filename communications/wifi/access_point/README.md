#Communications
## Wifi
### Access Point

Code to creat ESP32 own WiFi network and acts as a hub (Just like WiFi router) for one or more stations is called Acces Point (AP).
The maximum number of stations that can connect to it is limited to five.
	
###Code
* [acces_point.ino](acces_point.ino)
```cpp
#include <WiFi.h>

/* Put your SSID & Password */
const char* ssid = "ESP32";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(9600);
  
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
 }
void loop() {}
```

### Libraries
* Wifi library by [Arduino](https://www.arduino.cc/) - Installed from the Arduino IDE Library Management
![WiFi_library](wifi/WiFi_library.png)