#include <CheapStepper.h>

CheapStepper stepper (8,9,10,11);

boolean runter = true;
int x; 
int StepsFenster;
int location;
int b;

void rollo (int location); 

void setup() {

  stepper.setRpm (10); // Drehzahl hier einstellen (6 RPM -22 RPM) Drehzahl gegen Drehmoment
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  for (x; digitalRead(2)==HIGH; x++)
    {
      runter = true;
      stepper.step(runter);
  }
  StepsFenster=0;
  for (StepsFenster; digitalRead(3)==HIGH;StepsFenster++) 
    {
      runter = false;
      stepper.step(runter);
  }
  Serial.print("Steps between open and closed window: ");
  Serial.print(StepsFenster);
  Serial.print("Current step: ");
  Serial.print(stepper.getStep());
}


void loop() {
  void rollo (int location){
  int steppos=0;
  int locationinsteps;
  locationinsteps=(StepsFenster*(100/location));
  
  if (locationinsteps>steppos)
  {
    runter = true;
    stepper.moveTo (runter, locationinsteps);
    steppos=steppos+Stepsfenster;
  }
  
  if (locationinsteps<stepstaken)
  {
    runter = false;
    locationinsteps= steppos-locationinsteps;
    stepper.moveTo (runter, locationinsteps);
    steppos=steppos-locationinsteps;
  }
}
}
