#include <CheapStepper.h>

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
  
  setupStepper();
  setupRollo();
}

void loop() {                  //Loop schleife, hier wird das Rollo gesteuert und die Sensorwerte ausgegeben
  
  if (Serial.available() > 0) {   //Wenn ein Serial zugang da ist wird integer location desen wert gleich gesätzt
    int location = Serial.read();
    rollo(location);
  }//Die funktion rollo kriegt dann den Wert vom Serial

  int temp_sensor = analogRead(A8); //Auslesen des temp_sensor an Pin
  int temp_celsius = map(temp_sensor, 0, 410, -50, 150); //Umwandeln in Grad Celsius
  int foto_sensor =analogRead(A1);
  int foto_base100= map(foto_sensor, 0, 410, -50, 150);

  Serial.write(getSerialOutput(foto_base100, temp_celsius).c_str());

  
  /*Serial.print(101);
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
  Serial.print("\n");*/
  delay (1000);
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

