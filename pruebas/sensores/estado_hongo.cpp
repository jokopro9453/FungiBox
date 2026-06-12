#include "estado_hongo.h"

// Se establecen las variables fijas con los constructores
Incubacion::Incubacion(){
  max_temp = 22.0;
  min_temp = 18.0;
  max_hum = 70;
  min_hum = 60;
}

Induccion::Induccion(){
  max_temp = 18.0;
  min_temp = 15.0;
  max_hum = 90;
  min_hum = 85;
}

Fructificacion::Fructificacion(){
  max_temp = 20.0;
  min_temp = 18.0;
  max_hum = 85;
  min_hum = 80;
}

void Hongo::vent(float temp, int hum){
  if(temp > max_temp || hum > max_hum){
    ventilador = true;
  } else {
    ventilador = false;
  }
}
// Funciones de control del ambiente 
void Hongo::regular_hum(int hum){
  if(hum < min_hum){
    humidificador = true; 
  } else {
    humidificador = false;
  }
}

void Hongo::regular_temp(float temp){
  if (temp < min_temp){
    cama_calor = true;
  } else{
    cama_calor = false;
  }
}

