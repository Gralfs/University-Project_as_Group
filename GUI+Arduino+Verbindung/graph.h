#ifndef GRAPH_H
#define GRAPH_H

#include <QDebug>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QPen>
#include <QtCharts/QLegend>

QT_CHARTS_USE_NAMESPACE

#include "arduinoreader.h"

class Graph : public QMainWindow
{
    Q_OBJECT
public:
    explicit Graph(ArduinoReader *reader, QWidget *parent = 0);

signals:

public slots:
    void updateGraph(SerialInput);

private:
    ArduinoReader *reader;

    QChart *chart;
    QLineSeries *tempSeries;
    QLineSeries *lightSeries;
};

#endif // GRAPH_H
