#include <time.h>
#include <QtGlobal>
#include <QRandomGenerator>

float generar_temp(float temp){
    int dado = QRandomGenerator::global()->bounded(1,101);

    if (dado <= 40){
         return temp += 0.1f;
    } else if(dado <=80){
        return temp -= 0.1f;
    }else if(dado <=98){
        return temp;
    }else{
        return temp += 2.0f;
    }
}

int generar_hum(int hum){

    int dado = QRandomGenerator::global()->bounded(1,101);

    if (dado <= 40){
        return hum += 1;
    } else if(dado <=80){
        return hum -= 1;
    }else if(dado <=98){
        return hum;
    }else{
        return hum -= 5;
    }
}

float generar_co2(float co2){
    int moneda = QRandomGenerator::global()->bounded(0,2);

    if (moneda == 1){
        return co2 += 5.0f;
    }else{
        return co2;
    }
}

qint64 tomar_hora(){
    qint64 hora = time(nullptr);

    return hora*1000;
}