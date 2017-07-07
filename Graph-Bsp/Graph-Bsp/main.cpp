#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QPen>
#include <QtCharts/QLegend>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Erstellen der beiden Kurven
    QLineSeries *series = new QLineSeries();
    QLineSeries *series1 = new QLineSeries();


    //Werte der Punkte(hier Beispielwerte)
    *series1<<QPointF(0, 588)<<QPointF(10, 637) << QPointF(20, 723) << QPointF(30, 698) << QPointF(40, 888) << QPointF(50, 832)<<QPointF(60, 1023);
    *series<< QPointF(0, 22) << QPointF(10, 23) << QPointF(20, 24) << QPointF(30, 23) << QPointF(40, 23) << QPointF(50, 22)<<QPointF(60, 23);


    //Hinzufügen der Kurven zum Graphen
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addSeries(series1);
    QValueAxis *axisX = new QValueAxis; //X-Achse wird erstellt und zum Graphen hinzugefügt
    axisX->setTickCount(7);
    axisX->setTitleText(QString("Zeit in Sekunden")); //Benennung der X-Achse
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->setTitle("Sensordaten"); //Titel des Graphen

    //Farbgebung der beiden Kurven
    QPen pen1(QRgb(0xFF0000));
    series->setPen(pen1);

    QPen pen2(QRgb(0x000080));
    series1->setPen(pen2);

    //Erstellung der Y-Achse für die Temperaturwerte
    QValueAxis *axisYTemp = new QValueAxis;
    axisYTemp->setLinePenColor(series->pen().color());
    axisYTemp->setTitleText(QString("Tempertur in °C"));

    chart->addAxis(axisYTemp, Qt::AlignLeft); //Hinzufügen der Y-Achse zum Graphen
    series->attachAxis(axisX);
    series->attachAxis(axisYTemp);

    //Erstellung der Y-Achse für die Lichtwertewerte
    QValueAxis *axisYLight = new QValueAxis;
    axisYLight->setLinePenColor(series1->pen().color());
    axisYLight->setTitleText(QString("Lichtwert"));

    chart->addAxis(axisYLight, Qt::AlignRight); //Hinzufügen der Y-Achse zum Graphen
    series1->attachAxis(axisX);
    series1->attachAxis(axisYLight);




    QChartView *chartView = new QChartView(chart); //Erstellung des Graphen
    chartView->setRenderHint(QPainter::Antialiasing); //Antialiasing, damit keine Stufen auf den Kurven zu sehen sind


    QMainWindow window; //Erstellen des Fensters, welches den Graphen anzeigt
    window.setCentralWidget(chartView);
    window.resize(800, 600); //Fenstergröße
    window.show();

    return a.exec();
}
