#include "widget.h"
#include "ui_widget.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";
    temperature_value = 0.0;
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
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }else{
        qDebug() << "Couldn't find the Arduino\n";
    }
}

Widget::~Widget()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}

void Widget::readSerial()
{
    QString serialBuffer = "";
    QString temperature_value = "0";
    QString serialData = "";
    qDebug() << "Serialport works";
    QStringList buffer_split = serialBuffer.split(",");
    if(buffer_split.length()<3){
        serialData = arduino->readAll();
        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
        serialData.clear();
    }
    else{
        serialBuffer = "";
        qDebug() << buffer_split<<"\n";
        temperature_value = buffer_split[1];
        ui->label_3->setText(temperature_value);
    }

}

/*
void Widget::on_pushButton_2_clicked()   //Emergency stop
{
}
void Widget::on_pushButton_5_clicked()   //Shutdown the whole programm (maybe wanted for holidays)
{
}*/

void Widget::on_checkBox_stateChanged(int arg1)
{

    if (arg1 == 2){     //Set button colors when manuel mode is activated
        setStyleSheet("QPushButton#pushButton_2 { background-color: red; }\n"
                      "QPushButton#pushButton_5 { background-color: grey; }\n"
                      "QPushButton#pushButton_3 { background-color: yellow; }\n"
                      "QPushButton#pushButton_4 { background-color: black; }\n"
                      "QPushButton#pushButton_4 { color: white; }\n");
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->verticalSlider->setEnabled(true);
    }

    if (arg1 == 0){
        setStyleSheet("");
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->verticalSlider->setEnabled(false);
    }

}

void Widget::on_pushButton_3_clicked()   //Fully open blinds
{
    ui->verticalSlider->setValue(0);
    ui->label_2->setText("1");
}

void Widget::on_pushButton_4_clicked()   //Fully close blinds
{
    ui->verticalSlider->setValue(99);
    ui->label_2->setText("100");
}

void Widget::on_verticalSlider_sliderReleased()     //writting of sliderposition when released into text file
{
    int state = ui->verticalSlider->value();
    state = state + 1;
}

void Widget::on_verticalSlider_valueChanged(int state)      //Display of Sliderposition on label
{
    int posi = state +1;
    QString pos = QString::number(posi);
    ui->label_2->setText(pos);
}

