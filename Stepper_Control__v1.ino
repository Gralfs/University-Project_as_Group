#include <CheapStepper.h>

CheapStepper stepper (8,9,10,11);

boolean runter = true;
int x; 
int StepsFenster;
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
}

void position(boolean runter, int 

void loop() {
  
}

