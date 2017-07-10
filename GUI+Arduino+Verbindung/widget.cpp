#include "widget.h"
#include "ui_widget.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>



Widget::Widget(ArduinoReader *reader, QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    setStyleSheet("");                          //sets Buttons and Slider to Disabled for atumatic usage
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->verticalSlider->setEnabled(false);

    // connect to the arduino reader
    QObject::connect(reader, SIGNAL(newBlock(SerialInput)), this, SLOT(updateUILabels(SerialInput)));
}

Widget::~Widget() {
    delete ui;
}


void Widget::updateUILabels(SerialInput newBlock) {
    this->ui->label_6->setText(newBlock.temp);
    this->ui->label_3->setText(newBlock.licht);
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
//    slidertest(state);
                            //Tests if the Slider Value is between 1-100 for the motor
            //Haven't been able to send action to arduino
}

void Widget::on_verticalSlider_valueChanged(int state)            //Display of Sliderposition on label
{
    int posi = state +1;
    QString pos = QString::number(posi);
    ui->label_2->setText(pos);

}

int Widget::slidertest(int state)
{
    qDebug() << "SliderTest\n";
    qDebug() << "von Patrick Stadler\n";
    qDebug() << "Test guckt, ob der Sliderwert zwischen 1-100 liegt.\n";
    qDebug() << "widget.cpp\n";
    if (0<state<101){
        qDebug() << "Test erfolgreich";
    }
    else{
        qDebug() << "Test fehlgeschlagen";
    }
    return 0;
}
