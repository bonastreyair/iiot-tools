# Sensor
## Fotoresistor
Using the button to control states.

### Hardware
* ESP32
* [Foto-resistor](docs/datasheet_button.pdf) - [4donline Source](https://4donline.ihs.com/images/VipMasterIC/IC/OMRN/OMRN-S-A0001309768/OMRN-S-A0001309768-1.pdf?hkey=52A5661711E402568146F3353EA87419)

### Code
* [fotoresistor.ino](fotoresistor.ino)
```cpp
#define DARKNESS_RES  1000  // Resistance in darkness in KΩ
#define BRIGHTNESS_RES  15  // Resistance in brightness (10 Lux) in KΩ
#define CALIBRARION_RES 10  // Calibration resistance in KΩ
#define LDR_PIN         33  // LDR Pin
 
int voltage;
int ilumination;
 
void setup(){
   Serial.begin(9600);
   analogReadResolution(12);  // Sets the reading resolution value to 12 bits (0-4095)
}
 
void loop(){
   voltage = analogRead(LDR_PIN); // Reads the value from the pin in a 0-4095 resolution corresponding to a linear 0-3.3V        
 
   ilumination = ((long)V*DARKNESS_RES*10)/((long)BRIGHTNESS_RES*CALIBRARION_RES*(4096-V));  // Use if LDR between 33 & Vcc (like in the image)  
   
   Serial.println(ilum);   
   
   delay(1000);
}
```

### Libraries
* No needed libraries

### Image
* [Connection image](docs/fotoresistor.jpeg)
