#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);             //start and display window
    Widget w;
    w.show();

    return a.exec();
}
