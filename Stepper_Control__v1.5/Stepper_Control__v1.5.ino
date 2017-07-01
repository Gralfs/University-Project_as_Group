#include <CheapStepper.h>

CheapStepper stepper (8,9,10,11);

class Motor
{
  private:
  int StepsFenster;       // Speicher für steps zwischen Rollo zu und offen. NICHT 0-100 bereich! 
  int PositionInSteps;

  public:
  void SetStepsWindow (int value);      //Methoden
  int getStepsFenster();
  void SetPositionInSteps (int value);
  int getPositionInSteps();
  
};

//Methodendefinitionen 
void Motor::SetStepsWindow(int value)
{
  value = StepsFenster;
}

void Motor::SetPositionInSteps(int value)
{
  value = PositionInSteps;
}

int Motor::getStepsFenster()
{
  return StepsFenster;
}

int Motor::getPositionInSteps()
{
  return PositionInSteps;
}

boolean runter = true;
void rollo (int location); 

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
  }
}

void rollo (int location){
 
  Motor Rollo;                                                      
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

