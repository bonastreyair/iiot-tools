#define SCT013 34

void setup() {
  Serial.begin(9600);

}

void loop() {
  delay(3000);
  float Tension = 225.00;
  float Irms=lectura_consum_sct013(); //Corriente eficaz (A)
  float P=Irms*Tension; // P=IV (Watts)
  Serial.print("Irms: ");
  Serial.print(Irms,3);
  Serial.print("A, Potencia: ");
  Serial.print(P,3);  
  Serial.println("W");
 
}

float lectura_consum_sct013()
{
  float voltajeSensor;
  float corriente=0;
  float Sumatoria=0;
  long tiempo=millis();
  int N=0;
  while(millis()-tiempo<500)//Duración 0.5 segundos(Aprox. 25 ciclos de 50Hz)
  { 
    voltajeSensor = (analogRead(34) * (3.3 / 4095.0))/8;////voltaje del sensor
    corriente=voltajeSensor*25.5; //corriente=VoltajeSensor*(20A/1V)
    Sumatoria=Sumatoria+sq(corriente);//Sumatoria de Cuadrados
    N=N+1;
    delay(1);
  }
  Sumatoria=Sumatoria*2;//Para compensar los cuadrados de los semiciclos negativos.
  corriente=sqrt((Sumatoria)/N); //ecuación del RMS
  return(corriente);
}
