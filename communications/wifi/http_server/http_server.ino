#include <WiFi.h>
#include <WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "YourNetwork";  // Enter SSID here
const char* password = "YourPassword";  //Enter Password here

WebServer server(80);

void setup() {
  Serial.begin(9600);

  connectToNetwork();
  Serial.print("Your IP: ");       //After being connected to a network, our ESP32 should have a IP
  Serial.println(WiFi.localIP());  //Print this local IP assigned

  server.on("/", handle_OnConnect);
  server.on("/Hello", handle_hello);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
   if (WiFi.status() != WL_CONNECTED) { //If Wifi disconnected, it tries to recconect
    connectToNetwork();
  }
  server.handleClient();
  
}

void handle_OnConnect() {
  server.send(200, "text/html", "Write /Hello"); 
}

void handle_hello() {
 server.send(200, "text/html", "Hello-world!"); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
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
