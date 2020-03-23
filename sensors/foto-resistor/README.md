# Sensor
## Button
Using the button to control states.

### Hardware
* ESP32
* [Foto-resistor](docs/datasheet_button.pdf) - [4donline Source](https://4donline.ihs.com/images/VipMasterIC/IC/OMRN/OMRN-S-A0001309768/OMRN-S-A0001309768-1.pdf?hkey=52A5661711E402568146F3353EA87419)

### Code
* [fotoresistor.ino](fotoresistor.ino)
```cpp
const long A = 1000;     //Resistance in darkness in KΩ
const int B = 15;        //Resistance in brightness (10 Lux) in KΩ
const int Rc = 10;       //Calibration resistance in KΩ
const int LDRPin = 33;   //LDR Pin
 
int V;
int ilum;
 
void setup() 
{
   Serial.begin(115200);
   analogReadResolution(12);
}
 
void loop()
{
   V = analogRead(LDRPin);         
 
   //ilum = ((long)(1024-V)*A*10)/((long)B*Rc*V);  //use if LDR between GND & 33 
   ilum = ((long)V*A*10)/((long)B*Rc*(4096-V));    //use if LDR between 33 & Vcc (like in the image)
   //Serial.println(V);   
   Serial.println(ilum);   
   delay(1000);
}
```

### Libraries
* No needed libraries
### Image
* [Connection image](docs/fotoresistor.jpeg)
