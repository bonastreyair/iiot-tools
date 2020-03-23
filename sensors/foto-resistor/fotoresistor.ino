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
