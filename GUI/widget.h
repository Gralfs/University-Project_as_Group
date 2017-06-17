#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

/*private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();*/

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_verticalSlider_sliderMoved(int position);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
