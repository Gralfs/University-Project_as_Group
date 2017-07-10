#include "graph.h"

Graph::Graph(ArduinoReader *reader, QWidget *parent) : QMainWindow(parent) {
    this->reader = reader;

    //Hinzufügen der Kurven zum Graphen
    chart = new QChart();
    chart->setTitle("Sensordaten"); //Titel des Graphen
    chart->legend()->hide();

    // Temperaturkurve
    tempSeries = new QLineSeries(this->chart);
    QPen pen1(QRgb(0xFF0000));
    tempSeries->setPen(pen1);

    // Lichtkurve
    lightSeries = new QLineSeries(this->chart);
    QPen pen2(QRgb(0x000080));
    lightSeries->setPen(pen2);

    // Kurven hinzufügen
    chart->addSeries(tempSeries);
    chart->addSeries(lightSeries);

    // X-Achse erstellen
    QValueAxis *axisX = new QValueAxis; //X-Achse wird erstellt und zum Graphen hinzugefügt
    axisX->setTitleText(QString("Zeit in Sekunden"));
    axisX->setRange(0, 60);
    chart->addAxis(axisX, Qt::AlignBottom);

    // Erstellung der Y-Achse für die Temperaturwerte
    QValueAxis *axisYTemp = new QValueAxis;
    axisYTemp->setLinePenColor(tempSeries->pen().color());
    axisYTemp->setTitleText(QString("Tempertur in °C"));
    axisYTemp->setRange(0, 30);
    chart->addAxis(axisYTemp, Qt::AlignLeft);

    // Erstellung der Y-Achse für die Lichtwertewerte
    QValueAxis *axisYLight = new QValueAxis;
    axisYLight->setLinePenColor(lightSeries->pen().color());
    axisYLight->setTitleText(QString("Lichtwert"));
    axisYLight->setRange(0, 500);
    chart->addAxis(axisYLight, Qt::AlignRight);

    // Achsen und Graphen verbinden
    tempSeries->attachAxis(axisX);
    tempSeries->attachAxis(axisYTemp);
    lightSeries->attachAxis(axisX);
    lightSeries->attachAxis(axisYLight);

    QChartView *chartView = new QChartView(chart); //Erstellung des Graphen
    chartView->setRenderHint(QPainter::Antialiasing); //Antialiasing, damit keine Stufen auf den Kurven zu sehen sind

    this->setCentralWidget(chartView);
    this->resize(800, 600);

    // connect to the arduino reader
    QObject::connect(reader, SIGNAL(newBlock(SerialInput)), this, SLOT(updateGraph(SerialInput)));
}

void Graph::updateGraph(SerialInput newBlock) {
    static float x = 0;

    this->tempSeries->append(x, newBlock.temp.toFloat());
    this->lightSeries->append(x, newBlock.licht.toFloat());

    chart->axisX()->setRange(0, ((int)(x / 60) + 1) * 60);

    x += 1;
}
