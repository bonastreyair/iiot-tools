#include <SoftwareSerial.h>
 
const int Rx = 4; //Pinout Rx of ESP32
const int Tx = 3; //Pinout Tx of ESP32
 
SoftwareSerial Serialgps(Rx,Tx);
 
void setup()
{
   Serial.begin(115200); 
   Serialgps.begin(9600); //Starts gps communication with UART
}
 
void loop()
{  // Trying read new message for one second
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
   if (Serialgps.available()) //If there is a good signal
   {
      char data;
      data = Serialgps.read();
      Serial.print(data);
   }
  }
}
