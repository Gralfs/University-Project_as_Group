#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QByteArray>
#include <QtCharts/QtCharts>


using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


public slots:
    void readSerial();

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
    QSerialPort *arduino;
    static const quint16 arduino_mega_vendor_id = 9025;
    static const quint16 arduino_mega_product_id = 66;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;

};

#endif // WIDGET_H
