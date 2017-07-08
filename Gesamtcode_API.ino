#include <CheapStepper.h>

CheapStepper stepper (8,9,10,11);



int tempAnf = 1 ;//global, da Anfangswerte "tempAnf" bzw. "lichtAnf" nicht immer wieder 1 gesetzt werden soll
int lichtAnf = 1 ;
int temp_celsius;
int foto_base100;
int temp = temp_celsius; //optional: neuer Variablenname
int licht = foto_base100; //optional: neuer Variablenname
int location;

void saveE(int tempAnf, int lichtAnf,int temp,int licht);//Funktionsprototypen
void Vergleichsfkt(double temp, double licht);
int go_down ();
int go_up ();




class Arduino
{
  private:
  int StepsFenster;       // Speicher für steps zwischen Rollo zu und offen. NICHT 0-100 bereich! 
  int PositionInSteps;    //Position vom Rollo in Steps
  int Position100;        //Position vom Rollo von 0 bis 100

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

boolean runter = true;         //Boolean variable das der Steppermotor weiß ob er runter oder hoch fahren muss
void rollo (int location);     //Funktiondefinition für das ändern der Rollo position
Arduino Rollo;                  //Rollo als Arduino definiert 

int initialise () {                 //Hier wird das Rollo intialisiert 
  while (digitalRead(4)!=LOW)       //Das Rollo fährt einmal bis ganz nach Unten bis er zum unterem Kontakt kommt
    {
      runter = true;                //wenn runter=true fährt das Rollo runter
      stepper.step(runter);           //Steppermotor befehl das er unendlich lange runter fährt
      //Serial.print("While loop");     //Ausgabe while loop für debugging. Das man weiß wo sich der Arduino gerade befindet
  }
  int StepsFenster=0;                   //definition das die steps zwischen ganz unten und ganz oben gespeichert werden kann
  for (StepsFenster; digitalRead(3)==HIGH;StepsFenster++)    //Jetzt fährt das Rollo ganz nach Oben und zählt dabei die notwendigen Schritte
    {
      runter = false;    //jetztz ist runter=false also fährt das Rollo nach oben 
      stepper.step(runter);   //Das Rollo fährt so unendlich nach Oben
      //Serial.print(StepsFenster);    //Serial print für das Debugging
      //Serial.print("\n");
  }
  //Serial.print("TOTAL:");  //Weitere serial prints für das Debugging
  //Serial.print(StepsFenster);
  //Serial.print("\n");
  Rollo.SetPositionInSteps (0); //Jetzt wo wir wissen das das Rollo ganz oben ist können wir die Position definieren
  Rollo.SetStepsWindow (StepsFenster); //die nötigen steps um ganz nach unten zufahren wird in der Klasse gespeichert
}

void setup() {       //Setup beim starten vom Arduino
  Arduino Rollo;      //Klassen definition 
  stepper.setRpm (10); // Drehzahl hier einstellen (6 RPM -22 RPM) Drehzahl gegen Drehmoment
  Serial.begin(9600);   //Serial baud rate wird hier bestimmt 
  pinMode(4, INPUT_PULLUP);   //Die beiden kontakte für Rollo ganz offen und ganz zu, werden hier definiert 
  pinMode(3, INPUT_PULLUP);
  initialise (); //Hier wird das Rollo intialisiert
  //Serial.print("Setup"); //Serial ausgabe für Debugging, das man weiß wo sich das Programm gerade befindet
}

void loop() {                  //Loop schleife, hier wird das Rollo gesteuert und die Sensorwerte ausgegeben
    if (Serial.available() > 0){   //Wenn ein Serial zugang da ist wird integer location desen wert gleich gesätzt
    int location = Serial.read();
    rollo(location);}//Die funktion rollo kriegt dann den Wert vom Serial
    int temp_sensor = analogRead(A8); //Auslesen des temp_sensor an Pin
    int temp_celsius = map(temp_sensor, 0, 410, -50, 150); //Umwandeln in Grad Celsius
    int foto_sensor =analogRead(A1);
    int foto_base100= map(foto_sensor, 0, 410, -50, 150);
    Serial.print(101);
    Serial.print(",");
    Serial.print(temp_celsius);
    Serial.print(",");
    Serial.print(102);
    Serial.print(",");
    Serial.print(foto_base100);
    Serial.print(",");
    Serial.print(103);
    Serial.print(",");
    Serial.print(Rollo.getPosition100());
    Serial.print(",");
    Serial.print("STOP");
    Serial.print(Rollo.getStepsFenster());
    Serial.print(",");
    Serial.print("\n");
    delay (1000);
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
  if (temp>=25 && licht>=80)
    {
       go_down();
    }
  else if (licht<=20)
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
  if ((20<licht<80) || (temp<25 && licht>80))
    {
      location=0; //0 bzw. Wert des obersten steps 
    }
  return location; //weitergabe über Serial.print??
}











void rollo (int location){
  Serial.print("Rollo function:");
  Serial.print(Rollo.getStepsFenster());                                                     
  int StepsFenster =  Rollo.getStepsFenster();                                               
  int locationinsteps=(StepsFenster * (100/location));
  int pos=Rollo.getPositionInSteps();
  
  if (locationinsteps>pos)
  {
    runter = true;
    stepper.moveTo (runter, locationinsteps);
    int nStep = stepper.getStepsLeft();
    nStep=nStep/Rollo.getStepsFenster();
    while(stepper.getStepsLeft() != 0)
        {  
    nStep=(pos/Rollo.getStepsFenster())+nStep;
    Serial.print(nStep);
    Serial.print("\n");
        }
    Rollo.SetPositionInSteps(locationinsteps);
    }
 
  
  else if (locationinsteps<pos)
  {
    runter = false;
    stepper.moveTo (runter, locationinsteps);
        int nStep = stepper.getStepsLeft();
    nStep=nStep/Rollo.getStepsFenster();
    while(stepper.getStepsLeft() != 0)
        {  
    nStep=(pos/Rollo.getStepsFenster())-nStep;
    Serial.print(nStep);
    Serial.print("\n");
        }
    Rollo.SetPositionInSteps(locationinsteps);
  }
  else
  {
    return;
  }
  
}

