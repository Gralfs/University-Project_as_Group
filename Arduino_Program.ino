#include <CheapStepper.h>

CheapStepper stepper (8,9,10,11);


class Arduino
{
  private:
  int StepsFenster;       // Speicher für steps zwischen Rollo zu und offen. NICHT 0-100 bereich! 
  int PositionInSteps;
  int Position100;

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
  value = StepsFenster;
}

void Arduino::SetPositionInSteps(int value)
{
  value = PositionInSteps;
}

void Arduino::SetPosition100 (int value)
{
  value = Position100;
}

int Arduino::getStepsFenster()
{
  return StepsFenster;
}

int Arduino::getPositionInSteps()
{
  return PositionInSteps;
}

int Arduino::getPosition100()
{
  return Position100;
}

boolean runter = true;
void rollo (int location); 
Arduino Rollo;

int initialise () {
  Motor Rollo;
    if (digitalRead(2)!=HIGH)
    {
      runter = true;
      stepper.step(runter);
  }
  int StepsFenster=0;
  for (StepsFenster; digitalRead(3)==HIGH;StepsFenster++) 
    {
      runter = false;
      stepper.step(runter);
  }
 Rollo.SetStepsWindow (StepsFenster);  
}


void setup() {

  stepper.setRpm (10); // Drehzahl hier einstellen (6 RPM -22 RPM) Drehzahl gegen Drehmoment
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  initialise ();
}

void loop() {
    if (Serial.available() > 0){
    int location = Serial.read();
    rollo(location);
    int temp_sensor = analogRead(A8); //Auslesen des temp_sensor an Pin
    int temp_celsius = map(temp_sensor, 0, 410, -50, 150); //Umwandeln in Grad Celsius
    int foto_sensor =analogRead(A1);
    int foto_base100
//    Serial.print(101);
//    Serial.print(",");
    Serial.print(temp_celsius);
    Serial.print("|");
//    Serial.print(102);
//    Serial.print(",");
    Serial.print(foto_base100);
 /*   Serial.print(",");
    Serial.print(103);
    Serial.print(",");
    Serial.print(Rollo.getPosition100);
    Serial.print(666);*/
  }
}

void rollo (int location){
                                                       
  int locationinsteps;
  int StepsFenster =  Rollo.getStepsFenster();                                               
  locationinsteps=(StepsFenster*(100/location));
  int pos;
  pos=Rollo.getPositionInSteps();
  if (locationinsteps>pos)
  {
    runter = true;
    stepper.newMove (runter, locationinsteps);
    int nStep = stepper.getStepsLeft();
    nStep=nStep/Rollo.getStepsFenster();
    while(stepper.getStepsLeft() != 0)
        {  
    nStep=(pos/Rollo.getStepsFenster())+nStep;
    Serial.print(nStep);
        }
    Rollo.SetPositionInSteps(locationinsteps);
    }
 
  
  else if (locationinsteps<pos)
  {
    runter = false;
    stepper.newMove (runter, locationinsteps);
        int nStep = stepper.getStepsLeft();
    nStep=nStep/Rollo.getStepsFenster();
    while(stepper.getStepsLeft() != 0)
        {  
    nStep=(pos/Rollo.getStepsFenster())-nStep;
    Serial.print(nStep);
        }
    Rollo.SetPositionInSteps(locationinsteps);
  }
  else
  {
    return;
  }
  
}

