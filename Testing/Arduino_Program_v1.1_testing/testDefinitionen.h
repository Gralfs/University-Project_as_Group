#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#ifdef TEST

#include "test.h"

boolean intialisierungerfolgreich;

void testAnmeldung(){ 
  bool testResult = false;

  if(intialisierungerfolgreich==true)
	{testResult = true;}

	else {
testResult = false;
}
  
  APITest::printTestResult(testResult, "Anmeldung", "Frederik Läuferts",
  "Arduino Stepper-motor Steuerung", "testDefinitionen.h");
}


void runTests(){
  APITest::printTestStartHeader();
  
  // Hier sollen die eigenen Tests hinzugefuegt werden
  testAnmeldung();

  APITest::printTestEndFooter(); 
}
#endif //TEST

#ifdef TEST  // Nicht modifizieren
  #define RUNTEST runTests();
#else
  #define RUNTEST
#endif


#endif //TESTDEFINITIONEN_H
