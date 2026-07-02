#ifndef SQL_H
#define SQL_H
#include <QSqlQuery>

bool conectar();

void introducir(qint64 hora, float temp, int hum, float co2);



#endif // SQL_H
