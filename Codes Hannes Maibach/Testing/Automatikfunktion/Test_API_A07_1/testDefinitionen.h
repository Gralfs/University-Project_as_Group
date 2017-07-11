#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#ifdef TEST

#include "test.h"

extern int location;
extern int licht;
extern int temp;

void testAnmeldung(){ // Name frei waehlbar
  bool testResult=false ;

licht=900;  // Eigene Testimplementierung...
temp=30;
  if(location==100)
{testResult = true;
Serial.print("location:");
Serial.print(location);}
else {testResult = false;}
  // testResult kann bei einem erfolgreichen Test 
  // auf true gesetzt werden
  
  APITest::printTestResult(testResult, "Automatikfunktion", "Hannes Maibach",
  "Test des Richtwertevergleichs zu den Umweltszenarien mit anschließendem Anpassen der Rolloposition, hier: sonnig und heiß (A07/A08)", "testDefinitionen.h");
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
