#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#include "test.h"
#include "widget.h"

#ifdef TEST


void testValidSerialInput() {
  bool testResult = true;

  SerialInput parsedResult;
  bool result = Widget::parseSerialInput("1100110", &parsedResult);

  if (result == false) {
    APITest::printComment("Das Ergebnis sollte 'true' sein.");
    testResult = false;
  }

  if (parsedResult.licht != "100") {
    APITest::printComment("Der Lichtwert sollte '100' sein, stattdessen: " + parsedResult.licht);
    testResult = false;
  }

  if (parsedResult.temp != "100") {
    APITest::printComment("Der Temperaturwert sollte '100' sein, stattdessen: " + parsedResult.temp);
    testResult = false;
  }

  APITest::printTestResult(testResult,
  "Korrektes Parsing des Inputs",
  "Michael Schlangen",
  "Parsing der Serial Inputs, um neue Werte für Licht und Temperatur zu extrahieren",
  "testDefinitionen.h");
}


void testInvalidSerialInput() {
    bool testResult = true;

    SerialInput parsedResult;
    bool result = Widget::parseSerialInput("nicht ausreichend", &parsedResult);

    if (result == true) {
      APITest::printComment("Das Ergebnis sollte 'false' sein.");
      testResult = false;
    }

    APITest::printTestResult(testResult,
    "Korrekter Rückgabewert bei unvollständigem Input",
    "Michael Schlangen",
    "Das Parsing sollte erfolgreich abbrechen, wenn es noch nicht ausreichend Daten gibt.",
    "testDefinitionen.h");
}


void runTests(){
  APITest::printTestStartHeader(); // Nicht modifizieren

  // Hier sollen die eigenen Tests hinzugefuegt werden
  testInvalidSerialInput();
  testValidSerialInput();

  APITest::printTestEndFooter(); // Nicht modifizieren
}
#endif //TEST

#ifdef TEST  // Nicht modifizieren
  #define RUNTEST runTests();
#else
  #define RUNTEST
#endif


#endif //TESTDEFINITIONEN_H
