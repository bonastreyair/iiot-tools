#include <WiFi.h> //Includes the WiFi library

const char* ssid = "yourNetworkName"; //Change to your SSID Network which wants to connect
const char* password = "yourNetworkPassword"; //Change to your SSID Network which wants to connect

void setup() {
  Serial.begin(9600);
  
  scanNetworks();
  connectToNetwork();

  Serial.print("Your IP: ");       //After being connected to a network, our ESP32 should have a IP
  Serial.println(WiFi.localIP());  //Print this local IP assigned

}

void loop() {
  if (WiFi.status() != WL_CONNECTED) { //If Wifi disconnected, it tries to recconect
    connectToNetwork();
  }

}

void scanNetworks(){
  int numberOfNetworks = WiFi.scanNetworks();

  Serial.print("Number of networks found: ");
  Serial. println (numberOfNetworks);

  for (int i = 0; i < numberOfNetworks; i++) {
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));

    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));

    Serial.println("---------------------");
  }
}

void connectToNetwork() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting with ");
  Serial.print(ssid); //Print the network which you want to connect
  Serial.println();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("Connected to network");
}
