#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "chantier.h"
#include "intervenant.h"
#include <QMainWindow>
#include "QMediaPlayer"
#include "QMediaPlaylist"
#include "parking.h"
#include <QVBoxLayout>
#include "stat.h"
#include "employe.h"
#include "poste.h"
#include "fournisseur.h"
#include "equipements.h"
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display_listes();
    void playaudio();
    void playaudio1();
    void refresh_stat();
    intervenat gettmp(){return tmp_inter;}
    Employe tmpemploye;
    poste tmpposte ;
    void refresh();
    void refreshma();
    bool modi(QString,QString);


Ui::MainWindow *ui;

private slots:
    void on_pushButton_clicked();

    void on_modifierchantier_clicked();

    void on_id_chmo_activated(const QString &arg1);
void arduinowork();
void updatelcd(QString);

    void on_tabchantier_activated(const QModelIndex &index);

    void on_supprimerchantier_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_modifierchantier_3_clicked();

    void on_pushButton_4_toggled(bool checked);

    void on_pushButton_4_clicked();

    void on_supprimerchantier_3_clicked();

    void on_tabcha_activated(const QModelIndex &index);

    void on_pb_ok1_clicked();

    void on_pushButton_5_toggled(bool checked);

    void on_pb_ok1_2_clicked();

    void on_pushButton_6_toggled(bool checked);

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_4_activated(const QString &arg1);




    void on_comboBox_5_activated(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void initialiser_formulaire();

    //void on_pb_ok1_clicked();

    //void on_comboBox_5_activated(const QString &arg1);

    bool verifier_formulaire_ajout_employe();

bool verifier_formulaire_ajout_poste();








    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_modifierchantier_6_clicked();

    void on_pushButton_21_clicked();
    void on_pb_ok1_5_clicked();
void on_comboBox_7_activated(const QString &arg1);
void on_pushButton_22_toggled(bool checked);
void on_tabcha_2_activated(const QModelIndex &index);

    void on_supprimerchantier_5_clicked();



    void on_comboBox_stat_type_currentTextChanged();




    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_supprimeremploye_clicked();

    void on_pushButton_18_clicked();

    void on_supprimerposte_2_clicked();

    void on_modifierchantier_4_clicked();

    void on_modifierchantier_2_clicked();

    void on_pb_ok1_3_clicked();

    void on_pb_ok1_4_clicked();

    void on_comboBox_13_activated(const QString &arg1);

    void on_checkBox_2_clicked();

    void on_comboBox_11_activated(const QString &arg1);

    void on_checkBox_clicked();

    void on_comboBox_12_activated(const QString &arg1);

    void on_comboBox_8_activated(const QString &arg1);

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_comboBox_6_activated(const QString &arg1);

    void on_pushButton_19_clicked();

    void on_comboBox_15_activated(const QString &arg1);

    void on_pb_ok1_6_clicked();

    void on_modifier_clicked();

    void on_supprimer_clicked();

    void on_pushButton_23_clicked();

    void on_comboBox_17_activated(const QString &arg1);

    void on_chercher_equi_clicked();

    void on_modifier_equi_clicked();

    void on_supprimer_equi_clicked();

    void on_comboBox_14_activated(const QString &arg1);

    void on_comboBox_16_activated(const QString &arg1);

    void on_tabWidget_11_tabBarClicked(int index);

    void on_pushButton_20_clicked();

    void on_actualiser_clicked();

    void on_connexion_4_clicked();

    void on_pushButton_envoyer_clicked();

    void on_pushButton_envoyer_2_clicked();

    void on_comboBox_18_activated(const QString &arg1);

    void on_pushButton_24_clicked();

    void on_pushButton_envoyer_3_clicked();

    void on_pushButton_envoyer_4_clicked();

    void on_pushButton_25_clicked();

private:
    //Ui::MainWindow *ui;
    chantier tmp_chantier;
    intervenat tmp_inter;
    QMediaPlaylist* music1;
    QMediaPlayer* music;
    parking tmp_parking;
    QVBoxLayout* mainLayout;
    Stat s;
    fournisseur f;
    equipements e1;
    Arduino a;
    QByteArray info;
    QByteArray data;
    QString alldata;
};
#endif // MAINWINDOW_H



