#ifndef ARDUINOREADER_H
#define ARDUINOREADER_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

#include "serialinputparser.h"

class ArduinoReader : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoReader(QObject *parent = 0);
    ~ArduinoReader();

signals:
    void newBlock(SerialInput newBlock);

public slots:
    void readSerial();

private:
    QSerialPort *arduino;
    static const quint16 arduino_mega_vendor_id = 9025;
    static const quint16 arduino_mega_product_id = 66;

    SerialInputParser parser;
};

#endif // ARDUINOREADER_H
