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

    setStyleSheet("");                          //sets Buttons and Slider to Disabled for atumatic usage
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->verticalSlider->setEnabled(false);

    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";

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
        qDebug() << arduino->isOpen()<<endl;
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

// parse serial input
bool Widget::parseSerialInput(QString inputString, SerialInput* result) {
    // check, whether there is any input
    QStringList bufferSplit = inputString.split('|');

    // return false when there is no data
    if (bufferSplit.length() < 2) {
        return false;
    }

    // parse light
    result->licht = bufferSplit.at(0);
    result->licht = result->licht.remove(0, result->licht.indexOf(",") + 1);

    // parse temp
    result->temp = bufferSplit.at(0);
    result->temp = result->temp.remove(result->temp.indexOf(","), 100);

    return true;
}

// read data from the serial port
void Widget::readSerial()
{
    // this will hold the parsed result.
    SerialInput result;

    if (Widget::parseSerialInput(serialBuffer, &result)) {
        // update ui with new data
        ui->label_3->setText(result.licht);
        ui->label_6->setText(result.temp);

        // reset serial buffer
        serialBuffer = "";
        serialData.clear();
    } else {
        // update data
        serialData = arduino->readAll();
        serialBuffer += QString::fromStdString(serialData.toStdString());
    }
}


void Widget::on_pushButton_2_clicked()                           //Emergency stop
{
    ui->label->setText("STOP");
                                                                //stops the shutters imidiatly
}

void Widget::on_pushButton_5_clicked()                          //restart the whole programm
{
    ui->label->setText("Restart");
                                                                //Needed when errors occur or the steps are not correct anymore
}

void Widget::on_checkBox_stateChanged(int arg1)
{

    if (arg1 == 2){                                             //Set button colors when manuel mode is activated
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

    if (arg1 == 0){                                              //Set buttons to diasbled when in automatic mode
        setStyleSheet("");
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->verticalSlider->setEnabled(false);
    }

}

void Widget::on_pushButton_3_clicked()                           //Fully open blinds
{
    ui->verticalSlider->setValue(0);
    ui->label_2->setText("1");
        //Haven't been able to send action to arduino
}

void Widget::on_pushButton_4_clicked()                           //Fully close blinds
{
    ui->verticalSlider->setValue(99);
    ui->label_2->setText("100");
    //Haven't been able to send action to arduino
}

void Widget::on_verticalSlider_sliderReleased()                  //writting of sliderposition when released into text file
{
    int state = ui->verticalSlider->value();
    state = state + 1;
    //Haven't been able to send action to arduino
}

void Widget::on_verticalSlider_valueChanged(int state)            //Display of Sliderposition on label
{
    int posi = state +1;
    QString pos = QString::number(posi);
    ui->label_2->setText(pos);

}
