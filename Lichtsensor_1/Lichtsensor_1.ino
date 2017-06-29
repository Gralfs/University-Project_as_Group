int eingang = A1;
int foto_sensor = 0; 
int Fotowerte [5];
int i;
int t=500;
bool runter_licht=false;
int lichtstaerke = 510; //Anpassen

void setup()
{
Serial.begin(9600); 

}

void loop()
{




for (i=0; i<5; i++){
   
foto_sensor =analogRead(eingang);

Serial.print("Sensorwert = " ); 
Serial.println(foto_sensor);
   
   Fotowerte[i] = foto_sensor;
  
   
   delay(t);
   }
   
}



