#ifndef SIMULADOR_SENSOR_H
#define SIMULADOR_SENSOR_H
#include <QtGlobal>

float generar_temp(float temp);

int generar_hum(int hum);

float generar_co2(float co2);

qint64 tomar_hora();

#endif // SIMULADOR_SENSOR_H
