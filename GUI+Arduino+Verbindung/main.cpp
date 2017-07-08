#include "widget.h"
#include <QApplication>

#define TEST
#include "testdefinition.h"

int main(int argc, char *argv[])
{
    RUNTEST

    QApplication a(argc, argv);             //start and display window
    Widget w;
    w.show();

    return a.exec();
}
