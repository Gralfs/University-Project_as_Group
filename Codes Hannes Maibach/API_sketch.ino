int tempAnf = 1 ;//global, da Anfangswerte "tempAnf" bzw. "lichtAnf" nicht immer wieder 1 gesetzt werden soll
int lichtAnf = 1 ;
int temp;
int licht;
temp = mittelwert_t; //optional: neuer Variablenname
licht = mittelwert_f; //optional: neuer Variablenname

void saveE(int tempAnf, int lichtAnf,int temp,int licht);//Funktionsprototypen
void Vergleichsfkt(double temp, double licht);
int go_down ();
int go_up ();



void setup ()

void loop() 
{
  // put your main code here, to run repeatedly:
  saveE(tempAnf, lichtAnf, temp, licht); //Funktionsaufruf von saveE (und Vergleichsfunktion(und go_up/go_down))   
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
  if (temp>=25 && licht>=800)
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
  delay(300000);
  if ((200<licht<800) || (temp<25 && licht>800))
    {
      location=0; //0 bzw. Wert des obersten steps 
    }
  return location; //weitergabe über Serial.print??
}


