void setup() {
   // put your setup code here, to run once:
 
 }
 void loop() {
   // put your main code here, to run repeatedly:
 
 int Comp_light(int);
 int Comp_temp(int);
 //Funktionsprototypen der Vergleichsfunktionen für Richtwertvergleich
  int Comp_temp(int temp)
 //Temperatur Vergleichsfunktion
    {
    int x;
    if (temp>Richtwert)
    {
 //Normierung der Temperaturwerte
     
      x=temp/Richtwert; 
     //Verhältniswert schaffen für Rolloeinstellung
      x*=100
   
    return x; 
   
    }
  }
 
  int Comp_light(int light)
  {
   int x;
   if (light>Richtwert)
   {
    x=light/Richtwert
    //Verhältniswert für Rolloeinstellung, gegf Licht normieren
    x*=100 
    return x;
   }
