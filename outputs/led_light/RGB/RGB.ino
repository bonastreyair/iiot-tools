const int BluePIN = 4; 
const int GreenPIN = 3; 
const int RedPIN = 5;
 
void setup() {
  Serial.begin(9600);    //start serial port
  pinMode(RedPIN , OUTPUT);  //pinout as output
  pinMode(GreenPIN , OUTPUT);  //pinout as output
  pinMode(BluePIN , OUTPUT);  //pinout as output
}
 
void loop()
   {    Color(255 ,0 ,0) ;//Red
        delay(1000); 
        Color(0,255 ,0) ;//Green
        delay(1000);
        Color(0 ,0 ,255) ;//Blue
        delay(1000);
    //If you have only digital output, you can't send these values.
    //Because you only send 1 or 0. When you send these values with
    //digital output, you really send 1 at the same time in all outputs.
    //For that reason, led will be white
        Color(13,227,201); // Mix Color or White
        delay(1500);
        Color(0,0,0);
        delay(1500);
   }

void Color(int R, int G, int B)
{
  digitalWrite(RedPIN, R); 
  digitalWrite(GreenPIN, G);
  digitalWrite(BluePIN, B);
}
