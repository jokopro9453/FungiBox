#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLineSeries>
#include <QSqlQueryModel>
#include <QDateTime>

// Cambiar formato de los datos capturados de la DB a datos legibles para la tabla.

class ModeloHistorial : public QSqlQueryModel {
public:
    using QSqlQueryModel::QSqlQueryModel;


    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {

        if (role == Qt::DisplayRole && index.column() == 0) {
            qint64 milisegundos = QSqlQueryModel::data(index, role).toLongLong();
            QDateTime fecha = QDateTime::fromMSecsSinceEpoch(milisegundos);
            return fecha.toString("dd/MM/yyyy HH:mm");
        }
        return QSqlQueryModel::data(index, role);
    }
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_monitoreo_btn_clicked();

    void on_ctrl_manual_btn_clicked();

    void on_config_btn_clicked();

    void actualizar_sistema();

    void actualizar_datos();

    void on_volver_btn_clicked();

    void on_Volver_2_clicked();

    void on_Actualizar_btn_clicked();

    void activar_ventilador(int potencia);

    void activar_cama_calor(int potencia);

    void activar_humidificador(int potencia);

    void on_volver_config_clicked();

    void on_guardar_config_clicked();

private:
    Ui::MainWindow *ui;

    float temp = 18.0f;
    int hum = 60;
    float co2 = 700.0f;

    float max_temp, min_temp, max_co2, min_co2;

    int max_hum, min_hum;

    bool vent_activo, humid_activo, cama_activa;

    QTimer *timer;

    QLineSeries *serie_temp;
    QLineSeries *serie_hum;
    QLineSeries *serie_co2;

    QLineSeries *serie_temp_manual;
    QLineSeries *serie_hum_manual;
    QLineSeries *serie_co2_manual;

    QChart *chart_temp_manual;
    QChart *chart_hum_manual;
    QChart *chart_co2_manual;

    float last_temp_save = -1000.0f;

    int last_hum_save = -10;

    qint64 last_time_save = 0;
};
#endif // MAINWINDOW_H
