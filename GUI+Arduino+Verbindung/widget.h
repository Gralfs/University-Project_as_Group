#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QByteArray>
#include <QtCharts/QtCharts>

#include "arduinoreader.h"
#include "serialinputparser.h"


using namespace std;

namespace Ui {
    class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(ArduinoReader *reader, QWidget *parent = 0);
    ~Widget();


public slots:
    void updateUILabels(SerialInput newBlock);

private slots:
    void on_pushButton_3_clicked();         //Slots for buttons, slider and checkbox
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_verticalSlider_sliderReleased();
    void on_verticalSlider_valueChanged(int value);


private:
    Ui::Widget *ui;                         //private class for the serial communication between the PC and the arduino
};

#endif // WIDGET_H
