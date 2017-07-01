#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QByteArray>


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
    void repaint();
    void readSerial();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
/*    void on_pushButton_2_clicked();
     void on_pushButton_5_clicked();*/

    void on_checkBox_stateChanged(int arg1);

    void on_verticalSlider_sliderReleased();

    void on_verticalSlider_valueChanged(int value);

private:
    Ui::Widget *ui;
    QSerialPort *arduino;
    static const quint16 arduino_mega_vendor_id = 9025;
    static const quint16 arduino_mega_product_id = 66;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
    double temperature_value;
};

#endif // WIDGET_H
