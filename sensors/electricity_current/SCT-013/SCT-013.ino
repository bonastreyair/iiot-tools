#include <WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

#define TMPPIN 32
#define SCT013 34

/*
const char* WIFIUser = "CIM-UPC";
const char* WIFIPassword = "Fundaci0CIM00";
*/
const char* WIFIUser = "AulaAutomatica";
const char* WIFIPassword = "ticsFcim";

char MQTTClientName[]="ESP3";
const char* MQTTUser = "";
const char* MQTTPassword = "";
WiFiClient espClient;
PubSubClient client(espClient); //Crea el client TCPIP


void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFIUser,WIFIPassword);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado, dirección IP: ");
  Serial.println(WiFi.localIP());

  client.setServer("10.12.13.62",1883);
  
}

void loop() {
  if (!client.connected())
  {
    Serial.println("reconnecting");
    reconnect();
  }

  lectura_sensor_TMP36();

  print_consum();
 
}

void print_consum(){
  delay(12000);
  float Tension = 225.00;
  float Irms=lectura_consum_sct013(); //Corriente eficaz (A)
  String voltage_s = String(Tension,2);
  client.publish("ESP3/SCT013/Tension",voltage_s.c_str());
  float P=Irms*Tension; // P=IV (Watts)
  Serial.print("Irms: ");
  Serial.print(Irms,3);
  Serial.print("A, Potencia: ");
  String corriente_s = String(Irms,2);
  client.publish("ESP3/SCT013/Corriente",corriente_s.c_str());
  Serial.print(P,3);  
  Serial.println("W");
  String potencia_s = String(P,2);
  client.publish("ESP3/SCT013/Potencia",potencia_s.c_str());
     
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

void lectura_sensor_TMP36(){
  delay (15000);  
  int reading = analogRead(TMPPIN);
  //Serial.print("Reading: ");
  //Serial.println(reading);
  float voltage = reading * 3.3;
  voltage /= 4095.0;
  float temp_TMP36 = (voltage * 50);
  
  Serial.print("Temperatura_TMP36: ");
  Serial.println(temp_TMP36);
  String temp_TMP36_s = String(temp_TMP36,2);
  client.publish("ESP3/TMP36/Temperatura",temp_TMP36_s.c_str()); 

  Serial.println();
}

void reconnect()
{
    client.connect(MQTTClientName,MQTTUser,MQTTPassword);
  if (client.connected()){
    Serial.println("Conectado a MQTT");
  }
  else {
    Serial.println("NO Conectado a MQTT");
    Serial.print("rc=");
    Serial.println(client.state());
    delay(5000);
  }
}
