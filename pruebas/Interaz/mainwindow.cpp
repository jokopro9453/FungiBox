#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Establecer conexion con la base de datos

    // qDebug() << "Drivers de SQL disponibles:" << QSqlDatabase::drivers();

    DB_fungibox = QSqlDatabase::addDatabase("QSQLITE", "conexion_fungi");  // Le hacemos saber a Qt que vamos a usar el formato SQLITE para la DB.
    DB_fungibox.setDatabaseName("C:/Users/liebr/OneDrive/Documentos/Pruebas_SQL/Fungibox.db"); //Direccion de la base de datos
    if (DB_fungibox.open()){
        qDebug() << "La conexion con la base de datos fue exitosa.";

    } else {
        qDebug() << "No se pudo establecer conexion con la base de datos.";
        qDebug() << "Error : " << DB_fungibox.lastError();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Implementacion para mostrar la tabla en la interfaz.

void MainWindow::on_btnMostrar_clicked(){

    //Llamamos db con la llave "conexion_fungi" que definimos en el constructor de la ventana

    QSqlDatabase db = QSqlDatabase::database("conexion_fungi");

    if (!DB_fungibox.open()){
        qDebug() << "No se pudo abrir la DB con el boton: " << DB_fungibox.lastError().text();
    } else {
         // qDebug() << "Si funciona";
    }

    // Hacemos la peticion para cargar la base de datos
    QSqlQuery QueryLoadData(db);

    // Pedimos que seleccione todo de la tabla "variables_ambientales". Para más adelante se puede cambiar por una cantidad de tiempo especifico o una cantidad de datos fija.

    if (QueryLoadData.exec("SELECT * FROM variables_ambientales")){

        qDebug() << "La consulta SQL se ejecutó correctamente.";

        ui->tableWidget->setRowCount(0);
        int fila = 0;
        while (QueryLoadData.next()){
            // qDebug() << "Leyendo registro fila:" << fila << " -> ID:" << QueryLoadData.value(0).toString();

            ui->tableWidget->insertRow(fila);

            ui->tableWidget->setItem(fila,0,new QTableWidgetItem(QString(QueryLoadData.value("id").toString())));
            ui->tableWidget->setItem(fila,1,new QTableWidgetItem(QString(QueryLoadData.value("tiempo").toString())));
            ui->tableWidget->setItem(fila,2,new QTableWidgetItem(QString(QueryLoadData.value("temperatura").toString())));
            ui->tableWidget->setItem(fila,3,new QTableWidgetItem(QString(QueryLoadData.value("humedad").toString())));
            ui->tableWidget->setItem(fila,4,new QTableWidgetItem(QString(QueryLoadData.value("co2").toString())));
            ui->tableWidget->setItem(fila,5,new QTableWidgetItem(QString(QueryLoadData.value("pot_ventilador").toString())));

            fila++;
        }
        qDebug() << "Total de filas insertadas en la tabla de Qt:" << fila;
    } else {
        qDebug() << "Error de consulta: " << QueryLoadData.lastError().text();
    }
        DB_fungibox.close();
    }



