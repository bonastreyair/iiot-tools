const int BluePIN = 22; 
const int GreenPIN = 21; 
const int RedPIN = 19;
 
void setup() {
  Serial.begin(9600);    //start serial port
  pinMode(RedPIN , OUTPUT);  //pinout as output
  pinMode(GreenPIN , OUTPUT);  //pinout as output
  pinMode(BluePIN , OUTPUT);  //pinout as output
}
 
void loop()
   {    Color(255 ,0 ,0) ;//Red
        delay(500); 
        Color(0,255 ,0) ;//Green
        delay(500);
        Color(0 ,0 ,255) ;//Blue
        delay(500);
        Color(13,227,201); // Mix Color
        delay(500);
        Color(0,0,0);
        delay(1000);
   }

void Color(int R, int G, int B)
{
  digitalWrite(RedPIN, R); 
  digitalWrite(GreenPIN, G);
  digitalWrite(BluePIN, B);
}
