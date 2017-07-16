//DEKLARATIONEN
//Variablen
int tempAnf = 1 ;//Variablen tempAnf, lichtAnf auf 1 gesetzt als Anfangswerte für die if-Bedingung in der loop-Schleife
int lichtAnf = 1 ;

int temp;//die von den Sensoren übergebenen Werte initialisieren 2 neue Variablen zur einfachen Handhabung in den Funktionen und Schleifen
int licht;
temp = mittelwert_t;//Anm.:mittwelwert_t ist der in Schleife ausgegebene Mittelwert der Temperatur
licht = mittelwert_f;//Anm.:mittelwert_f ist der in Schleife ausgegebene Mittelwert des Lichts

//Funktionsprototypen
void saveE(int tempAnf, int lichtAnf,int temp,int licht);
void Vergleichsfkt(double temp, double licht);
int go_down ();
int go_up ();

//IM HAUPTPROGRAMM:

void setup ()

void loop() 
{
  
  saveR(tempAnf, lichtAnf, temp, licht);                     //Auslösen des Schleifenkonstruktes zum Vergleich der Sensorwerte mit den Richtwerten der Umweltszenarien   
}


//FUNKTIONSDEFINITIONEN

void saveR(int tempAnf, int lichtAnf,int temp,int licht)   //Funktion zum Sparen der Ressourcen (läuft in Schleife)
    {                                                       // Nur wenn sich ein Wert ändert, d.h. ungleich dem Anfangswert ist, wird die Vergleichsfunktion geändert und ggf. die Rolloposition geändert
      if (temp != tempAnf || licht != lichtAnf)         
      {
        tempAnf=temp;                                       //die geänderten Sensorwerte bilden die neue Anfangswerte der Funktion
        lichtAnf=licht;   
        Vergleichsfkt(temp,licht);                
      }
    }

void Vergleichsfkt(double temp, double licht)      //Funktion zum Abgleich der Sensorwerte mit Richtwerten und Auslösen des Motors (automatisierte Rollosteuerung)
{
  if (temp>=25 && licht>=800)                    //Abfragen, ob Umweltszenario "Sommer" vorliegt, also hohe Temperatur und hohe Lichtintensität
    {
       go_down();                               //wenn ja, Rollo ganz runter fahren
    }
  else if (licht<=200)                          //Abfragen, ob Umweltszenario "Nacht" vorliegt, also sehr geringe Lichtintensität
    {
      go_down();                                //wenn ja, Rollo ganz runter fahren
    }
  else                                          //Abfragen, ob Umweltszenario "bedeckter Tag" vorliegt, also mittlere Lichtwerte
    {
      go_up();                                  //wenn ja, Rollo ganz nach oben fahren
    }
}


int go_down ()                  //Funktion gibt Signal/Wert zum Motorauslösen und damit zum Rollo runterfahren. Ggf. Position halten, falls die Position schon erreicht ist.
{
  location = 100;              //Rolloposition auf 100  setzen bzw. den Wert des untersten "steps" des Motors
  return location;             //Weitergabe der Rolloposition an nächste Funktion ermöglicht
}


int go_up ()                      //Funktion gibt Signal/Wert zum Motorauslösen und Rollo hochfahren. Ggf. Position halten, falls die Position schon erreicht ist.
{
  delay(300000);                   //Funktionsablauf pausiert kurz, falls nur eine irreguläre Störung vorliegt (z.B Fliege sitzt auf dem Lichtsensor)
                              
  if ((200<licht<800) || (temp<25 && licht>800)) // erneute Prüfung, ob sich die Sensorwerte weiterhin im Bereich des vorher angenommenen Szenario "bedeckter Tag" befinden
    {
      location=0;                 //Rolloposition auf 0 setzen bzw. den Wert des obersten "steps" des Motors 
    }
  return location;                //Weitergabe der Rolloposition an nächste Funktion ermöglicht
}


