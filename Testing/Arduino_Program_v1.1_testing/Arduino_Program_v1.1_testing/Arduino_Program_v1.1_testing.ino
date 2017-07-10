#include <CheapStepper.h>
#define TEST
#include "testDefinitionen.h"
#include "registration.h"

CheapStepper stepper (8,9,10,11);


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

int initialise () {  //Hier wird das Rollo intialisiert 
  boolean intialisierungerfolgreich = false;
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
  intialisierungerfolgreich = true;
}

void setup() { //Setup beim starten vom Arduino
  RUNTEST

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
    if(0 <= Serial.read() <= 100) {     //If loop das das Rollo nicht sich kaputt fährt
    int location = Serial.read();
    rollo(location);}//Die funktion rollo kriegt dann den Wert vom Serial
    else 
    {Serial.print("invalid position");
    }
    }
    int temp_sensor = analogRead(A8); //Auslesen des temp_sensor an Pin
    int temp_celsius = map(temp_sensor, 0, 410, -50, 150); //Umwandeln in Grad Celsius
    int foto_sensor =analogRead(A1);
    int foto_base100= map(foto_sensor, 0, 410, -50, 150);
    Serial.print(101);        //Sensorwerte werden auf das Serialport geschrieben 
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

