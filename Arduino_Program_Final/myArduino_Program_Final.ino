#include <CheapStepper.h>

CheapStepper stepper (8,9,10,11);


class Arduino
{
  private:
  int StepsFenster;                                // Speicher für steps zwischen Rollo zu und offen. NICHT 0-100 bereich! 
  int PositionInSteps;                             //Position vom Rollo in Steps
  int Position100;                                 //Position vom Rollo von 0 bis 100

  public:
  void SetStepsWindow (int value);      //Methoden
  int getStepsFenster();
  void SetPositionInSteps (int value);
  int getPositionInSteps();
  void SetPosition100 (int value);
  int getPosition100 ();
  
};

//Methodendefinitionen 
void Arduino::SetStepsWindow(int value)
{
  StepsFenster = value;
}

void Arduino::SetPositionInSteps(int value)
{
  PositionInSteps = value;
}

void Arduino::SetPosition100 (int value)
{
  Position100 = value;
}

int Arduino::getStepsFenster(void)
{
  return StepsFenster;
}

int Arduino::getPositionInSteps(void)
{
  return PositionInSteps;
}

int Arduino::getPosition100(void)
{
  return Position100;
}


//DEKLARATIONEN

boolean runter = true;         //Boolean variable das der Steppermotor weiß ob er runter oder hoch fahren muss
void rollo (int location);     //Funktiondefinition für das ändern der Rollo position
Arduino Rollo;                  //Rollo als Arduino definiert 

//VARIABLEN
//Temperatur

int temp_sensor;                           //Intwerte zwischen 0 bis 410
int temp_celsius = 0;                      //Umgerechnete Temperatur
int Temperaturwerte [60];
int mittelwert_t;
int sum_t;                                //Temperaturen addiert pro Minute
int tempAnf = 1 ;                         //global, da Anfangswerte "tempAnf" bzw. "lichtAnf" nicht immer wieder 1 gesetzt werden soll
int temp = mittelwert_t;                   //Anm.:mittwelwert_t ist der in Schleife ausgegebene Mittelwert der Temperatur
                                           //die von den Sensoren übergebenen Werte initialisieren 2 neue Variablen (int temp,int licht) zur einfachen Handhabung in den Funktionen und Schleifen

int i;
int location;                             //Rolloposition in Prozent (wobei 0 = ganz hochgefahen und 100 = Rollo ganz heruntergefahren)

//Licht
int eingang = A1; //Pinbelegung Lichtsensor
int foto_sensor ; 
int Fotowerte [60];
int sum_f;  //Lichtwerte addiert pro Minute
int mittelwert_f; 
int lichtAnf = 1 ;
int licht = mittelwert_f;                 //Anm.:mittelwert_f ist der in Schleife ausgegebene Mittelwert des Lichts


//Funktionsprototypen
void saveR(int tempAnf, int lichtAnf,int temp,int licht);
void Vergleichsfkt(double temp, double licht);
int go_down ();
int go_up ();





bool isAtTop() {
  return digitalRead(3) == LOW;
}

bool isAtBottom() {
  return digitalRead(4) == LOW;
}

void setupStepper() {
  stepper.setRpm (10); // Drehzahl hier einstellen (6 RPM -22 RPM) Drehzahl gegen Drehmoment
}

void driveUp() {
  stepper.step(false);
}

void driveDown() {
  stepper.step(true);
}

int setupRollo() {
  //Das Rollo fährt einmal bis ganz nach Unten bis er zum unterem Kontakt kommt
  while (!isAtBottom()) {
    driveDown();
  }

  //Jetzt fährt das Rollo ganz nach Oben und zählt dabei die notwendigen Schritte
  int StepsFenster = 0;
  for (StepsFenster; !isAtTop(); StepsFenster++) {
    driveUp();
  }
  
  Rollo.SetPositionInSteps (0); //Jetzt wo wir wissen das das Rollo ganz oben ist können wir die Position definieren
  Rollo.SetStepsWindow (StepsFenster); //die nötigen steps um ganz nach unten zufahren wird in der Klasse gespeichert
}

// Erstelle den String, der den Licht- und Temperaturwert ausgibt.
String getSerialOutput(int licht, int temp) {
  return String(licht) + "," + String(temp) + "|";
}

void setup() {       //Setup beim starten vom Arduino
  //Serial baud rate wird hier bestimmt 
  Serial.begin(9600);

  pinMode(4, INPUT_PULLUP);   //Die beiden kontakte für Rollo ganz offen und ganz zu, werden hier definiert 
  pinMode(3, INPUT_PULLUP);
  pinMode(12, OUTPUT); // Pin 12 ist ein Ausgang.s
  setupStepper();
  setupRollo();
}

void loop() {                  //Loop schleife, hier wird das Rollo gesteuert und die Sensorwerte ausgegeben
  if (100 <= Serial.available() >= 0) {   //Wenn ein Serial zugang da ist wird integer location desen wert gleich gesätzt
    location = Serial.read();
    rollo(location);
 }//Die funktion rollo kriegt dann den Wert vom Serial
 
  sum_t=0;
  sum_f=0;
  
  //Schleife für Sensoren
for (i=0; i<60; i++){

   //Temperatursensor
    temp_sensor = analogRead(A8); //Auslesen des temp_sensor an Pin
    temp_celsius = map(temp_sensor, 0, 410, -50, 150); //Umwandeln in Grad Celsius
    
    //Lichtsensor
    foto_sensor =analogRead(eingang);

    delay(1000);

      Temperaturwerte[i] = temp_celsius;
      Fotowerte[i] = foto_sensor;
     
      //Addieren der Werte
  sum_t=sum_t+Temperaturwerte[i]; 
  sum_f=sum_f+Fotowerte[i];
  
  }
  //Mittelwertberechnung
mittelwert_t=sum_t/60;
mittelwert_f=sum_f/60;


Serial.write(getSerialOutput(mittelwert_f, mittelwert_f).c_str());
  
 saveR( tempAnf, lichtAnf, temp, licht);                                 //Auslösen des Schleifenkonstruktes zum Vergleich der Sensorwerte mit den Richtwerten der Umweltszenarien   

}

//F U N K T I O N S D E F I N I T I O N E N

void saveR(int tempAnf, int lichtAnf,int temp,int licht)                //Funktion zum Sparen der Ressourcen (läuft in Schleife)
    {
      if (temp != tempAnf || licht != lichtAnf)                        // Nur wenn sich ein Wert ändert, wird die Vergleichsfunktion aufgerufen bzw. kann die Rolloposition geändert werden
      {
        tempAnf=temp;                                                  //geänderte Sensorwerte bilden neue Anfangswerte der Funktion
        lichtAnf=licht;   
        Vergleichsfkt(temp,licht);
      }
    }

void Vergleichsfkt(double temp, double licht)  //Funktion zum Abgleich der Sensorwerte mit Richtwerten und Auslösen des Motors (automatisierte Rollosteuerung)
{
  if (temp>=25 && licht>=800)             //Abfragen, ob Umweltszenario "Sommer" vorliegt, also hohe Temperatur und hohe Lichtintensität
    {
       go_down();                         //wenn ja, Rollo ganz runter fahren
    }
  else if (licht<=200)                    //Abfragen, ob Umweltszenario "Nacht" vorliegt, also sehr geringe Lichtintensität
    {
      go_down();                          //wenn ja, Rollo ganz runter fahren
    }
  else                                    //Abfragen, ob Umweltszenario "bedeckter Tag" vorliegt, also mittlere Lichtwerte
    {
      go_up();                            //wenn ja, Rollo ganz nach oben fahren
    }
}


int go_down ()                             //Funktion gibt Signal/Wert zum Motorauslösen und Rollo runterfahren, ggf. Position halten
{
  location = 100;                         //Rolloposition auf 100  setzen bzw. den Wert des untersten "steps" des Motors
  return location;  
}


int go_up ()                              //Funktion gibt Signal/Wert zum Motorauslösen und damit zum Rollo runterfahren. Ggf. Position halten, falls die Position schon erreicht ist.
  delay(300000);
  if ((200<licht<800) || (temp<25 && licht>800))
    {
      location=0;                      //Rolloposition auf 100  setzen bzw. den Wert des untersten "steps" des Motors
    }
  return location;                    //Weitergabe der Rolloposition an nächste Funktion ermöglicht
}



void rollo (int location){        //Rollo positions funktion. Hier wird berechnet wie viele Steps der Steppermotor fahren muss um die gewünschte Position zu erreichen 
  //Serial.print("Rollo function:");      //Serial print für Debugging
  //Serial.print(Rollo.getStepsFenster());                                                     
  int StepsFenster =  Rollo.getStepsFenster();                                               
  int locationinsteps=(StepsFenster * (100/location));  //Umrechnung auf steps... 
  int pos=Rollo.getPositionInSteps();
  
  if (locationinsteps>pos)      //if loop ob er runter oder hoch fahren muss
  {
    runter = true;      //hier fährt er runter
    stepper.moveTo (runter, locationinsteps);       //Stepper Befehl 
    /*int nStep = stepper.getStepsLeft();           //Gets steps left das man positions status zum GUI schicken kann. Noch nicht funktionsfähig.
    nStep=nStep/Rollo.getStepsFenster();
    while(stepper.getStepsLeft() != 0)
        {  
    nStep=(pos/Rollo.getStepsFenster())+nStep;
    Serial.print(nStep);
    Serial.print("\n");
        }
        */
    Rollo.SetPositionInSteps(locationinsteps);
    }
 
  
  else if (locationinsteps<pos)
  {
    runter = false;       //hier fährt er hoch
    stepper.moveTo (runter, locationinsteps);
    /*int nStep = stepper.getStepsLeft();
    nStep=nStep/Rollo.getStepsFenster();
    while(stepper.getStepsLeft() != 0)
        {  
    nStep=(pos/Rollo.getStepsFenster())-nStep;
    Serial.print(nStep);
    Serial.print("\n");
        }
        */
    Rollo.SetPositionInSteps(locationinsteps);
  }
  else
  {
    return;
  }
  
}

