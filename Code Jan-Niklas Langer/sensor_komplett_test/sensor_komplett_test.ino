#define TEST
#include "testLicht.h"
#include "testTemperatur.h"


//Temperatur
int TMP36 = A8; //Pinbelegung Temperatursensor
int temp_sensor; //Intwerte zwischen 0 bis 410
int temp_celsius = 0; //Umgerechnete Temperatur
int t = 1000; //Zeitspanne zwischen Wertabfragen;
int Temperaturwerte [60];
int mittelwert_t;
int sum_t; //Temperaturen addiert pro Minute

int i;

//Licht
int eingang = A1; //Pinbelegung Lichtsensor
int foto_sensor ; 
int Fotowerte [60];
int sum_f;  //Lichtwerte addiert pro Minute
int mittelwert_f; 


void setup() {


  // put your setup code here, to run once:
Serial.begin(9600); //Übertragung Serielle Schnittstelle
 pinMode(12, OUTPUT); // Pin 12 ist ein Ausgang. Zuständig für die Temperatur


}

void loop() {
 
  // put your main code here, to run repeatedly:
//Schleife für Mittelwertsberechnung

  sum_t=0;
  sum_f=0;
  //Schleife für Sensoren
for (i=0; i<60; i++){

   //Temperatursensor
    temp_sensor = analogRead(TMP36); //Auslesen des temp_sensor an Pin
    temp_celsius = map(temp_sensor, 0, 410, -50, 150); //Umwandeln in Grad Celsius
    //Lichtsensor

    foto_sensor =analogRead(eingang);

    
    
    delay(t);

      Temperaturwerte[i] = temp_celsius;
      Fotowerte[i] = foto_sensor;
     
      //Addieren der Werte
  sum_t=sum_t+Temperaturwerte[i]; 
  sum_f=sum_f+Fotowerte[i];


  
  }
  //Mittelwertberechnung
mittelwert_t=sum_t/60;
mittelwert_f=sum_f/60;

//Ausgabe
 Serial.print("Temperatur:"); 
   Serial.print(mittelwert_t); 
         Serial.println(",");

            Serial.print("Licht:"); 
           Serial.print(mittelwert_f); 
         Serial.println(",");
RUNTEST
RUNTEST
}
