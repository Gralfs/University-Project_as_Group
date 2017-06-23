#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
/*
void Widget::on_pushButton_2_clicked()   //Emergency stop
{
}
void Widget::on_pushButton_5_clicked()   //Shutdown the whole programm (maybe wanted for holidays)
{
}*/

void Widget::on_checkBox_stateChanged(int arg1)     //Set button colors when manuel mode is activated
{

    if (arg1 == 2){
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

void Widget::on_verticalSlider_sliderMoved(int state)        //state of slider
{
    int posi = state +1;
    QString pos = QString::number(posi);
    ui->label_2->setText(pos);
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
