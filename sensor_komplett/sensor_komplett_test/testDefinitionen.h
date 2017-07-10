#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#ifdef TEST

#include "test.h"

extern boolean sensorwerteausgabe;

void testAnmeldung(){ // Name frei waehlbar
  bool testResult = false;

  // Eigene Testimplementierung...

  if(sensorwerteausgabe==true)
{testResult = true;}
  // testResult kann bei einem erfolgreichen Test 
  // auf true gesetzt werden
  
  APITest::printTestResult(testResult, "Sensorwerte", "Jan-Niklas Langer",
  "Licht- und Temperaturwerte werden ausgegeben A03 A04", "testDefinitionen.h");
}


void runTests(){
  APITest::printTestStartHeader(); // Nicht modifizieren
  
  



  // Hier sollen die eigenen Tests hinzugefuegt werden
  testAnmeldung();

  APITest::printTestEndFooter(); // Nicht modifizieren
}
#endif //TEST

#ifdef TEST  // Nicht modifizieren
  #define RUNTEST runTests();
#else
  #define RUNTEST
#endif


#endif //TESTDEFINITIONEN_H
