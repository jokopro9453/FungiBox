#ifndef GRAFICAS_H
#define GRAFICAS_H

#include <QChart>
#include <QChartView>
#include <QLineSeries>

QChart* crear_grafico(QLineSeries *serie, QString variable);


#endif // GRAFICAS_H
