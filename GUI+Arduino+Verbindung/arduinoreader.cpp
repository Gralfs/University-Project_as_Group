#include "arduinoreader.h"

ArduinoReader::ArduinoReader(QObject *parent) : QObject(parent) {
    arduino = new QSerialPort(this);

    bool arduino_is_available = false;

    QString arduino_mega_port_name;
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            if((serialPortInfo.productIdentifier() == arduino_mega_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduino_mega_vendor_id)){
                arduino_is_available = true;
                arduino_mega_port_name = serialPortInfo.portName();
            }
        }
    }

    if(arduino_is_available){
        qDebug() << "Found the Arduino port...\n";

        arduino->setPortName(arduino_mega_port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));

        arduino->clear();
    } else {
        qDebug() << "Couldn't find the Arduino\n";
    }
}

ArduinoReader::~ArduinoReader() {
    if (arduino->isOpen()) {
        arduino->close();
    }
}

// read data from the serial port
void ArduinoReader::readSerial()
{
    bool result = this->parser.addInputString(this->arduino->readAll());

    if (result) {
        emit newBlock(this->parser.getData().last());
    }
}


