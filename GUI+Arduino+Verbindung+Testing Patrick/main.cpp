#include "widget.h"
#include "graph.h"
#include "arduinoreader.h"
#include <QtWidgets/QApplication>


#define TEST
#include "testdefinition.h"

int main(int argc, char *argv[])
{
    RUNTEST

    QApplication a(argc, argv);             //start and display window

    ArduinoReader reader;

    Widget w(&reader);
    w.show();

    Graph g(&reader);
    g.show();

    return a.exec();
}
