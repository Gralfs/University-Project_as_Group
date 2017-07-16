#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#ifdef TEST

#include "test.h"

extern int mittelwert_t;


void testAnmeldung(){ // Name frei waehlbar
  bool testResult=false ;

  // Eigene Testimplementierung...

  if(mittelwert_t>0)
{testResult = true;}
else {testResult = false;}
  // testResult kann bei einem erfolgreichen Test 
  // auf true gesetzt werden
  
  APITest::printTestResult(testResult, "Temperaturwerte", "Jan-Niklas Langer",
  "Temperaturwerte werden ausgegeben A04", "testTemperatur.h");
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
