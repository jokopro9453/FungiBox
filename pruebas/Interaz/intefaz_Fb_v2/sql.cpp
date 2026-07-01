#include "sql.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

bool conectar() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","conexion_fungi");
    db.setDatabaseName("C:/Users/liebr/OneDrive/Documentos/Pruebas_SQL/Fungibox.db");

    if(db.open()){
        qDebug() << "Conexion exitosa";

        return true;
    } else {
        qDebug() << "Se produjo un error: " << db.lastError();

        return false;
    }
}

void introducir(qint64 hora, float temp, int hum, float co2){

    QSqlDatabase db = QSqlDatabase::database("conexion_fungi");

    QSqlQuery query(db);

    query.prepare("INSERT INTO variables_ambientales (tiempo, temperatura, humedad, co2) " "VALUES (:tiempo, :temp, :hum, :co2)");

    query.bindValue(":tiempo", hora);
    query.bindValue(":temp", temp);
    query.bindValue(":hum", hum);
    query.bindValue(":co2", co2);

    if (query.exec()){
        //qDebug() << "Los datos se insertaron correctamente!!";
    } else {
        qDebug() << "Hubo un error al subir los datos: " << query.lastError();
    }

}