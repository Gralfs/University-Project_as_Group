#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //setStyleSheet("QPushButton#pushButton_2 { background-color: red; }\n"
                 // "QPushButton#pushButton_5 { background-color: grey; }\n");
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
/*
void Widget::on_pushButton_3_clicked()   //Fully open blinds
{

}

void Widget::on_pushButton_4_clicked()   //Fully close blinds
{

}

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
    }

    if (arg1 == 0){
        setStyleSheet("");
    }

}

//Slidersetup still missing

void Widget::on_verticalSlider_sliderMoved(int state)        //state of slider
{
    int posi = state +1;
    QString pos = QString::number(posi);
    ui->label_2->setText(pos);
/*    int position = 75;
    QString posit = QString::number(position);
    ui->label->setText(posit);
    ui->progressBar->setValue(position);*/
}
