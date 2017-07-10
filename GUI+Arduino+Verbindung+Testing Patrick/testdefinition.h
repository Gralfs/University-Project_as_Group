#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#include "test.h"
#include "serialinputparser.h"

#ifdef TEST


void testValidSerialInput() {
  bool testResult = true;

  SerialInputParser parser;
  parser.addInputString("658,23|");

  QList<SerialInput>* data = parser.getData();

  if (data->length() != 1) {
    APITest::printComment("Es sollte ein kompletter Block gefunden worden sein, stattdessen: " + QString(data->length()));
    testResult = false;
  }

  if (data->at(0).licht != "658") {
    APITest::printComment("Der Lichtwert sollte '658' sein, stattdessen: " + data->at(0).licht);
    testResult = false;
  }

  if (data->at(0).temp != "23") {
    APITest::printComment("Der Temperaturwert sollte '23' sein, stattdessen: " + data->at(0).temp);
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

    SerialInputParser parser;
    parser.addInputString("658,23");

    QList<SerialInput>* data = parser.getData();

    if (data->length() != 0) {
      APITest::printComment("Es sollte kein vollständiger Block gefunden worden sein, stattdessen: " + QString(data->length()));
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
