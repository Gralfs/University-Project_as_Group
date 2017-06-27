
#include <EEPROM.h>


int TMP36 = A0; //Pinbelegung Sensor, wird noch angepast
int temp_sensor; //Intwerte zwischen 0 bis 410
int temp_celsius = 0; //Umgerechnete Temperatur
int t = 1000; //Zeitspanne zwischen Temperaturabfragen;
int i;
int Werte [60];
int mittelwert;
int j;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //Übertragung Serielle Schnittstelle
}

void loop() {
// put your main code here, to run repeatedly:

for (j=1; j<2; j++){
for (i=0; i<60; i++){
   
   temp_sensor = analogRead(TMP36); //Auslesen des temp_sensor an Pin
   temp_celsius = map(temp_sensor, 0, 410, -50, 150); //Umwandeln in Grad Celsius
   
   Serial.print(temp_celsius); 
   Serial.println(" Grad Celsius");

   
   Werte[i] = temp_celsius;


  
   delay(t);
  }



  EEPROM.write(j, mittelwert); 
   
}

 
}
