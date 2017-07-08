#ifndef TEST_H
#define TEST_H

#include <string>
#include <QDebug>


static int s_testsPassed = 0;
static int s_testsFailed = 0;

class APITest {

private:
  /// \brief Nicht relevant: Ausgabe einer Linie
  static void printTestLine(){
    qDebug() << "-------------------------------------";
  }


  /// \brief Diese Funktion wird aufgerufen, wenn der Test erfolgreich war
  static void printTestSuccess(){
    s_testsPassed++;
    qDebug() << "Testergebnis | **Erfolgreich**\n";
    printTestLine();
  }

  /// \brief Diese Funktion wird aufgerufen, wenn der Test fehlgeschlagen ist
  static void printTestFail(){
    s_testsFailed++;
    qDebug() << "Testergebnis | **Fehlgeschlagen**\n";
    printTestLine();
  }

public:

  static void printComment(QString comment){
    qDebug() << comment;
  }

  /// \brief Setzt die Daten für den jeweiligen Test
  /// \param result Ergebnis des Tests true=Erfolgreich false=Fehlgeschlagen
  /// \param testName Name des Tests, damit dieser anschließend identifiziert werden kann
  /// \param autor Name des Autors, der den Test geschrieben hat
  /// \param testFall Was wird getestet. Ein Stichpunkt bzw. ein Satz genügt
  /// \param dateiName In welcher Datei befindet sich der Test
  static void printTestResult(const bool result, const char* testName, const char* autor, const char* testFall = "", const char* dateiName = ""){
    printTestLine();
    qDebug() << "Test | ";
    qDebug() << testName;
    qDebug() << "Geschrieben von | ";
    qDebug() << autor;
    qDebug() << "Was wird getestet  | ";
    qDebug() << testFall;
    qDebug() << "Dateiname | ";
    qDebug() << dateiName;

    if(result){
      printTestSuccess();
    }
    else {
      printTestFail();
    }
  }

  /// \brief Gibt den Header am Anfang der Tests aus
  static void printTestStartHeader() {
    printTestLine();
    qDebug() << "Starte Tests:";
  }

  /// \brief Gibt die Zusammenfassung am Ende der Tests aus
  static void printTestEndFooter(){
    qDebug() << endl;
    printTestLine();
    qDebug() << "Ergebnis: " << s_testsPassed << "erfolgreich, " << s_testsFailed << "fehlgeschlagen";
    printTestLine();
  }

};
#endif //TEST_H
