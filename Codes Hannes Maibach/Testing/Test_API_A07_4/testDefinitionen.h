#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#ifdef TEST

#include "test.h"

extern int location;
extern int licht;
extern int temp;
extern int tempAnf;
extern int lichtAnf;
void testAnmeldung(){ // Name frei waehlbar
  bool testResult=false ;

Serial.print("----tempAnf: ");
Serial.print(tempAnf);
Serial.print("----lichtAnf: ");
Serial.print(lichtAnf);
Serial.print("----location:");
Serial.print(location);
if(tempAnf==1)
{
 testResult = false;
}
else {testResult = true;}
  // testResult kann bei einem erfolgreichen Test 
  // auf true gesetzt werden
  
  APITest::printTestResult(testResult, "Ressourcensparfunktion", "Hannes Maibach",
  "Änderung der Messwerte löst Vergleichsfunktion aus (A07/A08)", "testDefinitionen.h");
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
