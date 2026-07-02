#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sql.h"
#include "graficas.h"
#include "simulador_sensor.h"
#include <QDateTime>
#include <QSqlQueryModel>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->StackedWidget->setCurrentIndex(0);

    ui->cama_on_label->setText("Apagado");
    ui->humid_on_label->setText("Apagado");
    ui->vent_on_label->setText("Apagado");

    min_temp = 15.0f;

    ui->temp_limit->setMinimum(min_temp);
    ui->temp_limit->setMaximum(22.0f);
    ui->temp_limit->setValue(22.0f);

    max_temp=ui->temp_limit->value();

    min_hum = 60;

    ui->hum_limit->setMinimum(min_hum);
    ui->hum_limit->setMaximum(90);
    ui->hum_limit->setValue(65);

    max_hum=ui->hum_limit->value();

    min_co2 = 400.0f;

    ui->co2_limit->setMinimum(min_co2);
    ui->co2_limit->setMaximum(2000.0f);
    ui->co2_limit->setValue(800.0f);

    max_co2=ui->co2_limit->value();

    ui->ultimos_dias->setMinimum(1);
    ui->ultimos_dias->setMaximum(30);
    ui->ultimos_dias->setValue(1);

    ui->potencia_cama_calor->setMinimum(0);
    ui->potencia_cama_calor->setMaximum(100);
    ui->potencia_cama_calor->setValue(0);

    ui->potencia_ventilador->setMinimum(0);
    ui->potencia_ventilador->setMaximum(100);
    ui->potencia_ventilador->setValue(0);

    ui->potencia_humidificador->setMinimum(0);
    ui->potencia_humidificador->setMaximum(100);
    ui->potencia_humidificador->setValue(0);

    if (conectar()){

        //Grafica de temperatura
        serie_temp = new QLineSeries(this);
        serie_temp->setPointsVisible(true);
        serie_temp->setColor(Qt::red);

        QChart *chart_temp = crear_grafico(serie_temp, "Temperatura (°C)");

        ui->temp_graf->setChart(chart_temp);
        ui->temp_graf->setRenderHint(QPainter::Antialiasing);

        //Grafica de humedad

        serie_hum = new QLineSeries(this);
        serie_hum->setPointsVisible(true);
        serie_hum->setColor(Qt::blue);

        QChart *chart_hum = crear_grafico(serie_hum, "Humedad (%)");

        ui->hum_graf->setChart(chart_hum);
        ui->hum_graf->setRenderHint(QPainter::Antialiasing);

        //Grafica CO2
        serie_co2 = new QLineSeries(this);
        serie_co2->setPointsVisible(true);
        serie_co2->setColor(Qt::green);

        QChart *chart_co2 = crear_grafico(serie_co2, "Co2 (ppm)");

        ui->co2_graf->setChart(chart_co2);
        ui->co2_graf->setRenderHint(QPainter::Antialiasing);

        timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, &MainWindow::actualizar_sistema);

        timer->start(5000);

        // Graficas de actualizacion manual

        //Temperatura Manual
        serie_temp_manual = new QLineSeries(this);
        serie_temp_manual->setPointsVisible(true);
        serie_temp_manual->setColor(Qt::red);

        chart_temp_manual = crear_grafico(serie_temp_manual, "Temperatura (°C)");

        ui->temp_manual_graph->setChart(chart_temp_manual);
        ui->temp_manual_graph->setRenderHint(QPainter::Antialiasing);

        //Humedad Manual
        serie_hum_manual = new QLineSeries(this);
        serie_hum_manual->setPointsVisible(true);
        serie_hum_manual->setColor(Qt::blue);

        chart_hum_manual = crear_grafico(serie_hum_manual, "Humedad (%)");

        ui->hum_manual_graph->setChart(chart_hum_manual);
        ui->hum_manual_graph->setRenderHint(QPainter::Antialiasing);

        //Co2 Manual

        serie_co2_manual = new QLineSeries(this);
        serie_co2_manual->setPointsVisible(true);
        serie_co2_manual->setColor(Qt::green);

        chart_co2_manual = crear_grafico(serie_co2_manual, "Co2 (ppm)");

        ui->co2_manual_graph->setChart(chart_co2_manual);
        ui->co2_manual_graph->setRenderHint(QPainter::Antialiasing);

        actualizar_datos();

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_monitoreo_btn_clicked()
{
    ui->StackedWidget->setCurrentIndex(1);
}


void MainWindow::on_ctrl_manual_btn_clicked()
{
    ui->StackedWidget->setCurrentIndex(2);
}


void MainWindow::on_config_btn_clicked()
{
    ui->StackedWidget->setCurrentIndex(3);
}

void MainWindow::actualizar_sistema(){
    qint64 hora = tomar_hora();

    float temp_anterior = temp;
    int hum_anterior = hum;

    temp = generar_temp(temp);

    if(ui->cama_calor->isChecked()){
        activar_cama_calor(ui->potencia_cama_calor->value());
        cama_activa = true;
    }else if(temp < min_temp){
        activar_cama_calor(100);
        cama_activa = true;
    }else{
        cama_activa = false;
    }

    if (cama_activa){
        ui->cama_on_label->setText("Encendida");
    }else{
        ui->cama_on_label->setText("Apagado");
    }

    ui->temp_label->setText(QString::number(temp)+ " °C");

    hum = generar_hum(hum);
    if(ui->humidificador->isChecked()){
        activar_humidificador(ui->potencia_humidificador->value());
        humid_activo = true;
    } else if(hum < min_hum){
        activar_humidificador(100);
        humid_activo = true;
    }else{
        humid_activo = false;
    }

    if(humid_activo){
        ui->humid_on_label->setText("Encendido");
    }else{
        ui->humid_on_label->setText("Apagado");
    }

    ui->hum_label->setText(QString::number(hum)+ " %");

    co2 = generar_co2(co2);

    if(ui->ventilador->isChecked()){
        activar_ventilador(ui->potencia_ventilador->value());
        vent_activo = true;

    } else if(temp > max_temp || hum > max_hum || co2 > max_co2){

        activar_ventilador(100);
        vent_activo = true;
    }else{
        vent_activo=false;
    }

    if (vent_activo){
        ui->vent_on_label->setText("Encendido");
    } else{
        ui->vent_on_label->setText("Apagado");
    }

    ui->co2_label->setText(QString::number(co2) + " ppm");

    qint64 diez_min_ms = 600000;

    qint64 cinco_min_ms = diez_min_ms/2;

    float delta_temp = 0.5f;
    int delta_hum = 5;

    bool timeout = (hora - last_time_save >= diez_min_ms);

    bool cambio_brusco_temp = (qAbs(temp - last_temp_save) >= delta_temp);

    bool cambio_brusco_hum =  (qAbs(hum - last_hum_save) >= delta_hum);

    if (last_time_save == 0){
        timeout = true;
    }

    if(timeout){

        introducir(hora,temp,hum,co2);

        last_temp_save = temp;
        last_time_save = hora;
        last_hum_save = hum;

        //qDebug() << "Ultima temperatura guardada: " << last_temp_save << " | Ultima hora guardada: " << last_time_save;
    } else if (cambio_brusco_temp){
        introducir(hora,temp,hum,co2);

        last_temp_save = temp;
        last_time_save = hora;
        last_hum_save = hum;
        if(!cama_activa && !vent_activo && (qAbs(temp-temp_anterior)>=delta_temp)){

            QApplication::beep();

            QMessageBox alerta_temp;
            alerta_temp.setIcon(QMessageBox::Warning);
            alerta_temp.setWindowTitle("Variacion Anormal!!");
            alerta_temp.setText("La temperatura a variado de una manera anormal, te sugerimos revisar los sensores o controlarla de forma manual.");
            alerta_temp.setStandardButtons(QMessageBox::Ok);
            alerta_temp.setDefaultButton(QMessageBox::Ok);

            alerta_temp.exec();
        }
    } else if (cambio_brusco_hum){
        introducir(hora,temp,hum,co2);
            if(!humid_activo && !vent_activo &&(qAbs(hum-hum_anterior)>=delta_hum)){

                QApplication::beep();

                QMessageBox alerta_hum;
                alerta_hum.setIcon(QMessageBox::Warning);
                alerta_hum.setWindowTitle("Variacion Anormal!!");
                alerta_hum.setText("La humedad a variado de una manera anormal, te sugerimos revisar los sensores o controlarla de forma manual.");
                alerta_hum.setStandardButtons(QMessageBox::Ok);
                alerta_hum.setDefaultButton(QMessageBox::Ok);

                alerta_hum.exec();

            }
        }

    qint64 max_time = hora;

    qint64 min_time;

    QDateTime tiempo_min;
    QDateTime tiempo_max;

    serie_temp->append(hora, temp);
    const auto ejes_temp = ui->temp_graf->chart()->axes(Qt::Horizontal);
    if (!ejes_temp.isEmpty()) {
        if (hora - serie_temp->at(0).x() < cinco_min_ms){
            min_time = serie_temp->at(0).x();
        } else {
            min_time = hora - cinco_min_ms;
        }


        tiempo_min = QDateTime::fromMSecsSinceEpoch(min_time);
        tiempo_max = QDateTime::fromMSecsSinceEpoch(max_time);

        ejes_temp.at(0)->setRange(tiempo_min, tiempo_max);
    }

    serie_hum->append(hora, hum);
    const auto ejes_hum = ui->hum_graf->chart()->axes(Qt::Horizontal);
    if (!ejes_hum.isEmpty()) {
        ejes_hum.at(0)->setRange(tiempo_min, tiempo_max);
    }

    serie_co2->append(hora, co2);
    const auto ejes_co2 = ui->co2_graf->chart()->axes(Qt::Horizontal);
    if (!ejes_co2.isEmpty()) {
        ejes_co2.at(0)->setRange(tiempo_min, tiempo_max);
    }
}
void MainWindow::on_volver_btn_clicked()
{
    ui->StackedWidget->setCurrentIndex(0);
}


void MainWindow::on_Volver_2_clicked()
{
    on_volver_btn_clicked();
}

//crear tablas de datos

void MainWindow::actualizar_datos(){
    serie_temp_manual->clear();
    serie_hum_manual->clear();
    serie_co2_manual->clear();

    qint64 tiempo_ms = static_cast<qint64>(ui->ultimos_dias->value()) * 86400000LL;

    qint64 hora_actual = QDateTime::currentMSecsSinceEpoch();

    qint64 filtro_tiempo = hora_actual - tiempo_ms;

    QSqlDatabase db = QSqlDatabase::database("conexion_fungi");

    // Temperatura manual

    QSqlQuery query_temp(db);

    query_temp.prepare("SELECT tiempo, temperatura FROM variables_ambientales WHERE tiempo >= ? ORDER BY tiempo ASC");

    query_temp.addBindValue(filtro_tiempo);

    if (query_temp.exec()){

        while (query_temp.next()){
            qint64 x_tiempo = query_temp.value(0).toLongLong();
            double y_temp = query_temp.value(1).toDouble();

            serie_temp_manual->append(x_tiempo,y_temp);
        }

        ModeloHistorial *modelo_temp_manual = new ModeloHistorial(this);

        query_temp.first();
        query_temp.previous();

        modelo_temp_manual->setQuery(std::move(query_temp));

        modelo_temp_manual->setHeaderData(0,Qt::Horizontal,"Fecha / Hora");
        modelo_temp_manual->setHeaderData(1,Qt::Horizontal,"Temperatura (C°)");

        ui->tabla_temp->setModel(modelo_temp_manual);
        ui->tabla_temp->resizeColumnsToContents();

        ui->tabla_temp->scrollToBottom();

        qint64 min_time;

        QDateTime tiempo_min;

        QDateTime tiempo_max;

        if (serie_temp_manual->count() > 0) {
            const auto ejes_X = chart_temp_manual->axes(Qt::Horizontal);
            const auto ejes_Y = chart_temp_manual->axes(Qt::Vertical);

            if (!ejes_X.isEmpty() && !ejes_Y.isEmpty()) {
                if (hora_actual - serie_temp_manual->at(0).x() < filtro_tiempo){
                    min_time = serie_temp_manual->at(0).x();
                } else {
                    min_time = hora_actual - filtro_tiempo;
                }

                tiempo_min = QDateTime::fromMSecsSinceEpoch(min_time);
                tiempo_max = QDateTime::currentDateTime();

                ejes_X.at(0)->setRange(tiempo_min, tiempo_max);
            }
        }

        //Humedad manual

        QSqlQuery query_hum(db);

        query_hum.prepare("SELECT tiempo, humedad FROM variables_ambientales WHERE tiempo >= ? ORDER BY tiempo ASC");

        query_hum.addBindValue(filtro_tiempo);

        if (query_hum.exec()){

            while (query_hum.next()){
                qint64 x_tiempo = query_hum.value(0).toLongLong();
                double y_temp = query_hum.value(1).toDouble();

                serie_hum_manual->append(x_tiempo,y_temp);
            }

            ModeloHistorial *modelo_hum_manual = new ModeloHistorial(this);

            query_hum.first();
            query_hum.previous();

            modelo_hum_manual->setQuery(std::move(query_hum));

            modelo_hum_manual->setHeaderData(0,Qt::Horizontal,"Fecha / Hora");
            modelo_hum_manual->setHeaderData(1,Qt::Horizontal,"Humedad (%)");

            ui->tabla_hum->setModel(modelo_hum_manual);
            ui->tabla_hum->resizeColumnsToContents();

            ui->tabla_hum->scrollToBottom();

            if (serie_hum_manual->count() > 0) {
                const auto ejes_X = chart_hum_manual->axes(Qt::Horizontal);
                const auto ejes_Y = chart_hum_manual->axes(Qt::Vertical);

                if (!ejes_X.isEmpty() && !ejes_Y.isEmpty()) {
                    if (!ejes_X.isEmpty() && !ejes_Y.isEmpty()){
                    ejes_X.at(0)->setRange(tiempo_min, tiempo_max);
                    }
                }
            }
        }

        QSqlQuery query_co2(db);

        query_co2.prepare("SELECT tiempo, co2 FROM variables_ambientales WHERE tiempo >= ? ORDER BY tiempo ASC");

        query_co2.addBindValue(filtro_tiempo);

        if (query_co2.exec()){

            while (query_co2.next()){
                qint64 x_tiempo = query_co2.value(0).toLongLong();
                double y_temp = query_co2.value(1).toDouble();

                serie_co2_manual->append(x_tiempo,y_temp);
            }

            ModeloHistorial *modelo_co2_manual = new ModeloHistorial(this);

            query_co2.first();
            query_co2.previous();

            modelo_co2_manual->setQuery(std::move(query_co2));

            modelo_co2_manual->setHeaderData(0,Qt::Horizontal,"Fecha / Hora");
            modelo_co2_manual->setHeaderData(1,Qt::Horizontal,"Co2 (ppm)");

            ui->tabla_co2->setModel(modelo_co2_manual);
            ui->tabla_co2->resizeColumnsToContents();

            ui->tabla_co2->scrollToBottom();

            if (serie_co2_manual->count() > 0) {
                const auto ejes_X = chart_co2_manual->axes(Qt::Horizontal);
                const auto ejes_Y = chart_co2_manual->axes(Qt::Vertical);

                if (!ejes_X.isEmpty() && !ejes_Y.isEmpty()) {
                    ejes_X.at(0)->setRange(tiempo_min, tiempo_max);
                }
            }
        }
    }
}

void MainWindow::on_Actualizar_btn_clicked()
{
    actualizar_datos();
}

void MainWindow::activar_ventilador(int porcentaje_potencia){
    //Asumiremos las condiciones temp_ambiente = 20.0 °C, hum_ambiente = 50% y co2_ambiente = 400 ppm

    float dif_temp = (temp - 20.0) * (porcentaje_potencia*0.0005f); //0.0005 variacion aproximada del 5% con la potencia al 100%

    temp -= dif_temp;

    float dif_hum = (hum - 50) * (porcentaje_potencia*0.0005f); //0.0005 variacion aproximada del 5% con la potencia al 100%

    hum -= dif_hum;

    float dif_co2 = porcentaje_potencia*0.5f; // saca aproximadamente 50 ppm al 100%

    if(co2-dif_co2 >= min_co2){
        co2 -= dif_co2;
    }
}

void MainWindow::activar_cama_calor(int porcentaje_potencia){

    float dif_temp = porcentaje_potencia*0.01;

    temp += dif_temp;
}

void MainWindow::activar_humidificador(int porcentaje_potencia){

    float dif_hum = porcentaje_potencia*0.02;

    hum += dif_hum;
}
void MainWindow::on_volver_config_clicked()
{
    on_volver_btn_clicked();
}


void MainWindow::on_guardar_config_clicked()
{
    max_temp = ui->temp_limit->value();
    max_hum = ui->hum_limit->value();
    max_co2 = ui->co2_limit->value();
}

