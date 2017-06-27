
#include <EEPROM.h>


int TMP36 = A8; //Pinbelegung Sensor, wird noch angepast
int temp_sensor; //Intwerte zwischen 0 bis 410
int temp_celsius = 0; //Umgerechnete Temperatur
int t = 1000; //Zeitspanne zwischen Temperaturabfragen;
int i;
int Werte [60];
int mittelwert;
int j;
int sum;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //Übertragung Serielle Schnittstelle
 pinMode(12, OUTPUT); // Pin 12 ist ein Ausgang.

}

void loop() {
// put your main code here, to run repeatedly:

for (j=1; j<2; j++){
  sum=0;
for (i=0; i<60; i++){
   
    temp_sensor = analogRead(TMP36); //Auslesen des temp_sensor an Pin
    temp_celsius = map(temp_sensor, 0, 410, -50, 150); //Umwandeln in Grad Celsius
         Serial.print(temp_celsius); 
         Serial.println(" Grad Celsius");
    delay(t);


   
   Werte[i] = temp_celsius;

  sum=sum+Werte[i];
  
  
  }

mittelwert=sum/60;

  EEPROM.write(j, mittelwert); 
   
}
if (temp_sensor>100){
  digitalWrite(12, HIGH); // Schalte die LED an Pin12 an.
  delay(1000); // Warte 1000 Millisekunden.
  digitalWrite(12, LOW); // Schalte die LED an Pin12 aus.

  delay(1000); // Warte 1000 Millisekunden.
}
}

