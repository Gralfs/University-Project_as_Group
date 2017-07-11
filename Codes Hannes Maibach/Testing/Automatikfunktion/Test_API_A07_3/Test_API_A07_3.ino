#define TEST
#include "testDefinitionen.h"



//Temperatur
int TMP36 = A8; //Pinbelegung Temperatursensor
int temp_sensor; //Intwerte zwischen 0 bis 410
int temp_celsius = 0; //Umgerechnete Temperatur
int t = 100; //Zeitspanne zwischen Wertabfragen; //VORSICHT: Um beim Test nicht zu lange warten zu müssen, wurden die delay-Zeiten verkürzt. Eigentlich:t=1000
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

int tempAnf = 1 ;//global, da Anfangswerte "tempAnf" bzw. "lichtAnf" nicht immer wieder 1 gesetzt werden soll
int lichtAnf = 1 ;
int temp =mittelwert_f;
int licht= mittelwert_f;;
int location;
//optional: neuer Variablenname

void saveE(int tempAnf,int lichtAnf,int temp,int licht);//Funktionsprototypen
void Vergleichsfkt(double temp, double licht);
int go_down ();
int go_up ();



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

saveE(tempAnf,lichtAnf,temp,licht);



}

void saveE(int tempAnf, int lichtAnf,int temp,int licht) //Funktion zum Sparen der Ressourcen
    {
      if (temp != tempAnf || licht != lichtAnf)  // Nur wenn sich ein Wert ändert, wird die Vergleichsfunktion aufgerufen.
      {
        tempAnf=temp;   //geänderte Sensorwerte bilden neue Anfangswerte
        lichtAnf=licht;   
        Vergleichsfkt(temp,licht);
      }
    }

void Vergleichsfkt(double temp, double licht)  //Funktion zum Abgleich der Sensorwerte mit Richtwerten und Auslösen des Motors,evtl + 4.Bedingung
{ 
  RUNTEST       //TEST START
  
  if (temp>=25 && licht>=800)  //Richtwertevergleich der Sensordaten
    {
       go_down();
    }
  else if (licht<=200)
    {
      go_down();
    }
  else
    {
      go_up();
    }
}


int go_down ()  //Funktion gibt Signal/Wert zum Motorauslösen und Rollo runterfahren, ggf. Position halten
{
  location = 100; //100 bzw. Wert des untersten steps
  return location;  //weitergabe über Serial.print??
}


int go_up ()   //Funktion gibt Signal/Wert zum Motorauslösen und Rollo hochfahren, ggf. Position halten
{
  delay(300);                                     //VORSICHT: Um beim Test nicht zu lange warten zu müssen, wurden die delay-Zeiten verkürzt. Eigentlich:delay(300000)
  if ((200<licht<800) || (temp<25 && licht>800))
    {
      location=0; //0 bzw. Wert des obersten steps 
    }
  return location; //weitergabe über Serial.print??
}


