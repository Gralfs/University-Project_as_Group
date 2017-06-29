//Temperatur
int TMP36 = A8; //Pinbelegung Sensor, wird noch angepast
int temp_sensor; //Intwerte zwischen 0 bis 410
int temp_celsius = 0; //Umgerechnete Temperatur
int t = 1000; //Zeitspanne zwischen Temperaturabfragen;
int i;
int Temperaturwerte [60];
int mittelwert_t;
int j;
int sum_t; //Temperaturen addiert pro Minute

//Licht

int eingang = A1;
int foto_sensor ; 
int Fotowerte [60];
int sum_f;
int mittelwert_f;




void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //Übertragung Serielle Schnittstelle
 pinMode(12, OUTPUT); // Pin 12 ist ein Ausgang. Zuständig für die Temperatur


}

void loop() {
  // put your main code here, to run repeatedly:
//Schleife für Mittelwertsberechnung
for (j=1; j<2; j++){
  sum_t=0;

  //Schleife für Sensoren
for (i=0; i<60; i++){

   //Temperatursensor
    temp_sensor = analogRead(TMP36); //Auslesen des temp_sensor an Pin
    temp_celsius = map(temp_sensor, 0, 410, -50, 150); //Umwandeln in Grad Celsius
    //Lichtsensor

    foto_sensor =analogRead(eingang);

    Serial.print("Sensorwert = " ); 
    Serial.println(foto_sensor);
   
    
    
    delay(t);

      Temperaturwerte[i] = temp_celsius;
      Fotowerte[i] = foto_sensor;
      
  sum_t=sum_t+Temperaturwerte[i];
  sum_f=sum_f+Fotowerte[i];
  
  }
mittelwert_t=sum_t/60;
mittelwert_f=sum_f/60;


 Serial.print("Temperatur:"); 
   Serial.print(mittelwert_t); 
         Serial.println(",");

            Serial.print("Licht:"); 
           Serial.print(mittelwert_f); 
         Serial.println(",");
}

}
