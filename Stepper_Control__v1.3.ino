#include <CheapStepper.h>

CheapStepper stepper (8,9,10,11);

boolean runter = true;
int x; 
int StepsFenster;
int location;
int b;

void rollo (int location); 

int initialise () {
    if (digitalRead(2)!=HIGH)
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
  return StepsFenster; 
}

void setup() {

  stepper.setRpm (10); // Drehzahl hier einstellen (6 RPM -22 RPM) Drehzahl gegen Drehmoment
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  initialise ();
}

void loop() {
    if (Serial.available()){
    int location = Serial.read();
    rollo(location, StepsFenster);
  }
}

void rollo (int location, int Stepsfenster){
  int steppos=0;                                                            //Position des Rollos in steps
  int locationinsteps;                                                      //Umrechnung zu steps für rollo 
  locationinsteps=(StepsFenster*(100/location));
  
  if (locationinsteps>steppos)
  {
    runter = true;
    stepper.moveTo (runter, locationinsteps);
    steppos=steppos+StepsFenster;
  }
  
  if (locationinsteps<steppos)
  {
    runter = false;
    locationinsteps= steppos-locationinsteps;
    stepper.moveTo (runter, locationinsteps);
    steppos=steppos-locationinsteps;
  }
  return;
}

