#include "graficas.h"
#include <QDateTimeAxis>
#include <QValueAxis>
QChart* crear_grafico(QLineSeries *serie, QString variable){
    QChart *chart = new QChart();

    chart->addSeries(serie);

    QDateTimeAxis *ejeX = new QDateTimeAxis;

    ejeX->setTitleText("Tiempo");
    ejeX->setFormat("HH:mm:ss");

    ejeX->setTickCount(5);


    QValueAxis *ejeY = new QValueAxis;

    ejeY->setTitleText(variable);

    if (variable.contains("Temperatura")){
        ejeY->setRange(10.0,30.0);
    }else if (variable.contains("Humedad")) {
        ejeY->setRange(50,100);
    }else if (variable.contains("Co2")) {
        ejeY->setRange(400,1500);
    }else {
        ejeY->setRange(0.0,100.0);
    }


    chart->addAxis(ejeX, Qt::AlignBottom);
    chart->addAxis(ejeY, Qt::AlignLeft);
    serie->attachAxis(ejeX);
    serie->attachAxis(ejeY);

    chart->legend()->hide();


    return chart;
}