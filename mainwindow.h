#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSql/QSqlDatabase>
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "Ecaritatif.h"
#include "dons.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_modifier_clicked();

    void on_modifier_equi_clicked();


    void on_pushButton_3_clicked();

    void on_supprimer_clicked();

    void on_chercher_equi_clicked();

    void on_pb_ok1_clicked();

    void on_supprimer_equi_clicked();

    void on_actualiser_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;


    don  f;
    ecaritatif e;
};
#endif // MAINWINDOW_H
