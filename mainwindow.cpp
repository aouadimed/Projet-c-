#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chantier.h"
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include <QDebug>
#include <QCoreApplication>
#include <QSqlQueryModel>
#include <QComboBox>
#include "intervenant.h"
#include "QMediaPlayer"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "mailing/SmtpMime"
#include <stdio.h>
#include <string.h>
#include "connexion.h"
#include <QtPrintSupport>
#include <QPrintDialog>
#include <QGraphicsView>
#include "parking.h"
#include <QVBoxLayout>
#include "stat.h"
#include <QtCharts>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QStandardItemModel>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include "fournisseur.h"
#include "equipements.h"
#include "arduino.h"
#include "notification.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    int ret=a.connect_arduino();
    switch (ret){
    case(0):qDebug()<< "arduino is available and connected to :" << a.getarduino_port_name();
        break;
    case(1):qDebug()<< "arduino is available but not connected to :" << a.getarduino_port_name();
        break;
    case(-1):qDebug()<< "arduino is not available :";
    }
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(arduinowork()));

    /*  **************sout*******************  */
    ui->pushButton_4->setIcon((QIcon(":/images/on.png")));
    ui->pushButton_4->setIconSize(ui->pushButton_4->size());
    ui->pushButton_4->setCheckable(true);
    /*  **************ajout*******************  */
    ui->pushButton_2->setIcon((QIcon(":/images/7.png")));
    ui->pushButton_2->setIconSize(ui->pushButton_2->size());
    ui->pushButton->setIcon((QIcon(":/images/9.png")));
    ui->pushButton->setIconSize(ui->pushButton->size());
    /*  **************modif*******************  */
    ui->modifierchantier->setIcon((QIcon(":/images/1.png")));
    ui->modifierchantier->setIconSize(ui->modifierchantier->size());
    ui->modifierchantier_3->setIcon((QIcon(":/images/1.png")));
    ui->modifierchantier_3->setIconSize(ui->modifierchantier_3->size());
    /*  **************tafsi5*******************  */
    ui->supprimerchantier_3->setIcon((QIcon(":/images/3.png")));
    ui->supprimerchantier_3->setIconSize(ui->supprimerchantier_3->size());
    ui->supprimerchantier->setIcon((QIcon(":/images/3.png")));
    ui->supprimerchantier->setIconSize(ui->supprimerchantier->size());
    /*  ******************tabs*******************  */
    ui->tabchantier->setModel(tmp_chantier.afficher());
    ui->tabcha->setModel(tmp_inter.afficher());
    ui->tabcha_2->setModel(tmp_parking.afficher());

    /*  ************************************************  */


    music1 =new QMediaPlaylist();
    music1->addMedia(QUrl("qrc:/images/backgmusic.mp3"));
    music1->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer();
    music->setPlaylist(music1);
    music->play();
    music->setVolume(8);
    /*  **************refresh*******************  */
    ui->pushButton_5->setIcon((QIcon(":/images/refresh1.png")));
    ui->pushButton_5->setIconSize(ui->pushButton_5->size());
    ui->pushButton_5->setCheckable(true);
    ui->pushButton_6->setIcon((QIcon(":/images/refresh1.png")));
    ui->pushButton_6->setIconSize(ui->pushButton_6->size());
    ui->pushButton_6->setCheckable(true);
    ui->pushButton_22->setIcon((QIcon(":/images/refresh1.png")));
    ui->pushButton_22->setIconSize(ui->pushButton_22->size());
    ui->pushButton_22->setCheckable(true);
    /*  **************recher*******************  */
    ui->pb_ok1->setIcon((QIcon(":/images/4.png")));
    ui->pb_ok1->setIconSize(ui->pb_ok1->size());
    ui->pb_ok1_2->setIcon((QIcon(":/images/4.png")));
    ui->pb_ok1_2->setIconSize(ui->pb_ok1_2->size());
    /*  **************anu*******************  */
    ui->pushButton_3->setIcon((QIcon(":/images/60578.png")));
    ui->pushButton_3->setIconSize(ui->pushButton_3->size());
    ui->pushButton_7->setIcon((QIcon(":/images/60578.png")));
    ui->pushButton_7->setIconSize(ui->pushButton_7->size());
    ui->pushButton_8->setIcon((QIcon(":/images/60578.png")));
    ui->pushButton_8->setIconSize(ui->pushButton_8->size());
    ui->pushButton_9->setIcon((QIcon(":/images/60578.png")));
    ui->pushButton_9->setIconSize(ui->pushButton_9->size());
    ui->lcdNumber->display("__");
    mainLayout=new QVBoxLayout ;
    mainLayout->addWidget(s.Preparechart());
    ui->widget->setLayout(mainLayout);
    refresh();
    ui->verticalLayout_3->addWidget(tmpemploye.statistique());
    ui->verticalLayout_8->addWidget(tmpemploye.statistique2());//afficher stat (vertciallayout)

    ui->tableView->setModel(f.afficher());
    ui->tableView_2->setModel(e1.afficher());
    ui->comboBox_14->setModel(f.combo_box());





}

MainWindow::~MainWindow()
{
    delete ui;
    delete music;
    delete mainLayout;
    delete music1;
}


bool MainWindow::modi(QString a,QString b)
{
    /*QSqlQuery query;
    query.prepare("UPDATE parking SET res=:res WHERE id=:id");
    query.bindValue(":res",a);
    query.bindValue(":id",b);
    return query.exec();*/
}
void MainWindow::arduinowork()
{
//**********************med**************************
    QString n;
info = a.read_from_arduino();
QString j=QString::fromStdString(info.toStdString());
qDebug() << j;
parking p;
QString b= QString::number(1);
QSqlQuery query;
query.prepare("select nbr from parking WHERE id=:id");
query.bindValue(":id",b);
query.exec();
while(query.next())
{
n =query.value(0).toString();
}
if (j<=n)
{
updatelcd(j);
bool test =p.modi(j,b);
if (test)
{
a.write_to_arduino("2");
}
ui->tabcha_2->setModel(tmp_parking.afficher());
}
if(j>n)
{
a.write_to_arduino("3");
a.write_to_arduino("4");
}
//**************************************************************
data=a.read_from_arduino();
    QString DataAsString = QString(data);

    alldata=alldata+QString::fromStdString(data.toStdString());
    QStringList datasplit = alldata.split(".");
    int value = (datasplit.last().toInt());
    qDebug()<<  value;
    if((value>600)&&(value<1100)){
        ui->label_arduino->setText("ON");
    }else if (value<600){
        ui->label_arduino->setText("OFF");
    }
    if((value>600)&&(value<1100)){
        a.write_to_arduino("1");
    }else if(value<600){
        a.write_to_arduino("0");
    }


}
void MainWindow::updatelcd(QString c)
{ui->lcdNumber->display(c);
}
void MainWindow::display_listes()
{
    ui->tabchantier->setModel(tmp_chantier.afficher());
    ui->id_chmo->setModel(tmp_chantier.combo_box());
    ui->tabcha->setModel(tmp_inter.afficher());
    ui->comboBox_2->setModel(tmp_inter.combo_box());
    ui->tabcha_2->setModel(tmp_parking.afficher());
    ui->comboBox_6->setModel(tmp_parking.combo_box());
    ui->comboBox_18->setModel(tmp_inter.combo_box1());
    ui->widget->setLayout(mainLayout);
    refresh_stat();

}
void MainWindow::refresh_stat()
{
    if ( ui->widget->layout() != NULL )
    {
    QLayoutItem* item;
    while ( ( item = ui->widget->layout()->takeAt( 0 ) ) != NULL )
    {
    delete item->widget();
    delete item;
    }
    delete ui->widget->layout();
    }
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(s.Preparechart());
    ui->widget->setLayout(mainLayout);
}
void MainWindow::playaudio()
{

    QMediaPlayer * music =new QMediaPlayer();
    music->setMedia(QUrl("qrc:/images/Click2.mp3"));
    music->play();
}




void MainWindow::on_pushButton_clicked()
{
    int i=ui->lineeditid->text().toInt();
    QString p=ui->lineEditadres->text();
    int k=ui->lineEditsurface->text().toInt();
    int l=ui->lineEditbudget->text().toInt();
    QDate d= ui->dateEdit->date();
    chantier c(i,p,k,l,d);


    if ((i!='\0')&&(p!='\0')&&(k!='\0')&&(l!='\0'))
    {

    bool test = c.ajouter();
    if(test)

    {
        display_listes();
        playaudio();

        notification n;
        n.ajoutchantier();
        QMessageBox::information(nullptr,("Ajout chantier"),("chantier ajouté"));}
else
     {QMessageBox::warning(nullptr,("Ajout chantier"),("chantier non ajouté"));}
    }

    else QMessageBox::warning(nullptr,("Ajout chantier"),("pas de données"));


 }

void MainWindow::on_modifierchantier_clicked()
{

    int i=ui->id_chmo->currentText().toInt();
    QString b=ui->ad_chmo->text();
    int e=ui->sur_chmo->text().toInt();
    int f=ui->bud_chmo->text().toInt();
    QDate d= ui->date_chmo->date();
    chantier c(i,b,e,f,d);
    bool test=c.modifier();
    if(test)
    {
         display_listes();
         playaudio();
        QMessageBox::information(nullptr, QObject::tr("Modifier un chantier"),
                    QObject::tr("chantier modifier modifié.\n"
                                "Cliquez sur Ok pour continuer."), QMessageBox::Ok);
    }
    else

       QMessageBox::critical(nullptr, QObject::tr("Modifier un chantier"),
                   QObject::tr("Erreur!\n"
                               "Erreur de modification de le chantier.\n Veuillez réessayer."), QMessageBox::Ok);


}

void MainWindow::on_id_chmo_activated(const QString & )
{
    QString a=ui->id_chmo->currentText();
      QSqlQuery query;
      query.prepare("select * from chantier where ID_CHANTIER =:id_chantier");
      query.bindValue(":id_chantier", a);

      if (query.exec())
      {

          while (query.next()) {


               playaudio();
               ui->id_chmo->setCurrentText(query.value(0).toString());
               ui->ad_chmo->setText(query.value(1).toString());
               ui->sur_chmo->setText(query.value(2).toString());
               ui->bud_chmo->setText(query.value(3).toString());
                ui->date_chmo->setDate(query.value(4).toDate());

          }
      }
}



void MainWindow::on_tabchantier_activated(const QModelIndex &index)
{
    QString a=ui->tabchantier->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from chantier where ID_CHANTIER=:id_chantier");
    query.bindValue(":id_chantier", a);

    if (query.exec())
    {

        while (query.next()) {

            ui->lineEdit_7->setText(query.value(0).toString());
            ui->sup_id->setText(query.value(0).toString());
            ui->id_chmo->setCurrentText(query.value(0).toString());
            ui->ad_chmo->setText(query.value(1).toString());
            ui->sur_chmo->setText(query.value(2).toString());
            ui->bud_chmo->setText(query.value(3).toString());
            ui->date_chmo->setDate(query.value(4).toDate());


        }
    }
}

void MainWindow::on_supprimerchantier_clicked()
{

    int a=ui->sup_id->text().toInt();
    bool test=tmp_chantier.supprimer(a);

    if (a!='\0'){
    QMessageBox::StandardButton reponse = QMessageBox::question(this,"suppression","confirmer la suppression",QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {

        if(test)
        {
            playaudio();
            display_listes();
            QMessageBox::information(nullptr, QObject::tr("Supprimer un chantier"),
                        QObject::tr("Client supprimé.\n"
                                    "Click Ok to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un chantier"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else  return;}






}

void MainWindow::on_pushButton_2_clicked()
{
    int i=ui->lineEdit->text().toInt();
    QString p=ui->lineEdit_2->text();
    QString k=ui->lineEdit_3->text();
    int l=ui->lineEdit_4->text().toInt();
    QString d= ui->lineEdit_5->text();
    intervenat c(i,p,k,l,d);
    if ((i!='\0')&&(p!='\0')&&(k!='\0')&&(l!='\0')&&(d!='\0'))
    {
    bool test = c.ajouter();
    if(test)

    {   playaudio();
        display_listes();
        notification n;
        n.ajoutinter();}
else
     {QMessageBox::warning(nullptr,("Ajout intervenant"),("intervenant non ajouté"));}}
    else QMessageBox::warning(nullptr,("Ajout intervenant"),("pas de données"));

}

void MainWindow::on_comboBox_2_activated(const QString &)
{
     QString a=ui->comboBox_2->currentText();
      QSqlQuery query;
      query.prepare("select * from inter where ID =:idd");
      query.bindValue(":idd", a);

      if (query.exec())
      {

          while (query.next()) {


               playaudio();
               ui->comboBox_2->setCurrentText(query.value(0).toString());
               ui->lineEditadres_4->setText(query.value(1).toString());
               ui->lineEditsurface_4->setText(query.value(2).toString());
               ui->lineEditbudget_4->setText(query.value(3).toString());
               ui->lineEdit_6->setText(query.value(4).toString());

          }
      }
}

void MainWindow::on_modifierchantier_3_clicked()
{
    int i=ui->comboBox_2->currentText().toInt();
    QString p=ui->lineEditadres_4->text();
    QString k=ui->lineEditsurface_4->text();
    int l=ui->lineEditbudget_4->text().toInt();
    QString d= ui->lineEdit_6->text();
    intervenat c(i,p,k,l,d);
    bool test=c.modifier();
    if(test)
    {    playaudio();
         display_listes();
        QMessageBox::information(nullptr, QObject::tr("Modifier un intervenat"),
                    QObject::tr("un intervenat a été modifier.\n"
                                "Cliquez sur Ok pour continuer."), QMessageBox::Ok);
    }
    else

       QMessageBox::critical(nullptr, QObject::tr("Modifier un chantier"),
                   QObject::tr("Erreur!\n"
                               "Erreur de modification .\n Veuillez réessayer."), QMessageBox::Ok);



}






void MainWindow::on_pushButton_4_toggled(bool checked)
{


    if (checked){
        ui->pushButton_4->setIcon((QIcon(":/images/off.png")));
        ui->pushButton_4->setIconSize(ui->pushButton_4->size());
        playaudio();
        music->pause();

    }
   else  {
        ui->pushButton_4->setIcon((QIcon(":/images/on.png")));
        ui->pushButton_4->setIconSize(ui->pushButton_4->size());
        playaudio();
        music->play();
    }

}

void MainWindow::on_pushButton_4_clicked()
{

}


void MainWindow::on_supprimerchantier_3_clicked()
{



        int a=ui->lineEdit_23->text().toInt();
       bool test=tmp_inter.supprimer(a);
       if (a!='\0'){
    QMessageBox::StandardButton reponse = QMessageBox::question(this,"suppression","confirmer la suppression",QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {

        if(test)
        {
            playaudio();
            display_listes();
            QMessageBox::information(nullptr, QObject::tr("Supprimer un intervenant"),
                        QObject::tr("intervenant supprimé.\n"
                                    "Click Ok to exit."), QMessageBox::Cancel);

        }
        else{
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un intervenant"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        playaudio();}

    }
    else  return;}


}



void MainWindow::on_tabcha_activated(const QModelIndex &index)
{
    QString a=ui->tabcha->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from inter where ID=:idd");
    query.bindValue(":idd", a);

    if (query.exec())
    {

        while (query.next()) {
            playaudio();
            ui->lineEdit_23->setText(query.value(0).toString());
            ui->comboBox_2->setCurrentText(query.value(0).toString());
            ui->lineEditadres_4->setText(query.value(1).toString());
            ui->lineEditsurface_4->setText(query.value(2).toString());
            ui->lineEditbudget_4->setText(query.value(3).toString());
            ui->lineEdit_6->setText(query.value(4).toString());


        }
    }
}

void MainWindow::on_pb_ok1_clicked()
{


    if (ui->radioButton_3->isChecked())
    {
        QString type= ui->lineEdit_18->text() ;
        ui->tabchantier->setModel(tmp_chantier.chercher(type));
        playaudio();
    }

    if (ui->radioButton_2->isChecked())
    {
        QString type= ui->lineEdit_18->text() ;
        ui->tabchantier->setModel(tmp_chantier.chercherbug(type));
        playaudio();
    }

    if (ui->radioButton->isChecked())
    {
        QString type= ui->lineEdit_18->text() ;
        ui->tabchantier->setModel(tmp_chantier.cherchersur(type));
        playaudio();
    }
    if (!(ui->radioButton_3->isChecked())&&!(ui->radioButton_2->isChecked())&&!(ui->radioButton->isChecked()))
           { playaudio();
        QMessageBox::critical(nullptr, QObject::tr("cherche échoué"),
                               QObject::tr("aaaaa\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
    }



}

void MainWindow::on_pushButton_5_toggled(bool checked)
{

    if (checked){
        ui->pushButton_5->setIcon((QIcon(":/images/refresh2.png")));
        ui->pushButton_5->setIconSize(ui->pushButton_5->size());
        display_listes();
        ui->lineEdit_18->clear();
        ui->sup_id->clear();
        playaudio();

    }
   else  {
        ui->pushButton_5->setIcon((QIcon(":/images/refresh1.png")));
        ui->pushButton_5->setIconSize(ui->pushButton_5->size());
        display_listes();
        ui->lineEdit_18->clear();
        ui->sup_id->clear();
        playaudio();
    }



}

void MainWindow::on_pb_ok1_2_clicked()
{
    if (ui->radioButton_4->isChecked())
    {
        QString type= ui->lineEdit_19->text() ;
        ui->tabcha->setModel(tmp_inter.cherchernom(type));
        playaudio();
    }

    if (ui->radioButton_5->isChecked())
    {
        QString type= ui->lineEdit_19->text() ;
        ui->tabcha->setModel(tmp_inter.chercherprenom(type));
        playaudio();
    }

    if (ui->radioButton_6->isChecked())
    {
        QString type= ui->lineEdit_19->text() ;
        ui->tabcha->setModel(tmp_inter.cherchergsm(type));
        playaudio();
    }
    if (!(ui->radioButton_4->isChecked())&&!(ui->radioButton_5->isChecked())&&!(ui->radioButton_6->isChecked()))
           { playaudio();
        QMessageBox::critical(nullptr, QObject::tr("cherche échoué"),
                               QObject::tr("aaaaa\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_pushButton_6_toggled(bool checked)
{
    if (checked){
        ui->pushButton_6->setIcon((QIcon(":/images/refresh2.png")));
        ui->pushButton_6->setIconSize(ui->pushButton_6->size());
        display_listes();
        ui->lineEdit_19->clear();
        ui->lineEdit_23->clear();
        playaudio();

    }
   else  {
        ui->pushButton_6->setIcon((QIcon(":/images/refresh1.png")));
        ui->pushButton_6->setIconSize(ui->pushButton_6->size());
        display_listes();
        ui->lineEdit_19->clear();
        ui->lineEdit_23->clear();
        playaudio();
    }


}

void MainWindow::on_comboBox_activated(const QString &arg1)
{

 if(arg1=="ID")
    {
     if (ui->radioButton_7->isChecked())
     {
         ui->tabchantier->setModel(tmp_chantier.trier_id());
         playaudio();
     }
     if (ui->radioButton_8->isChecked())
     {
         ui->tabchantier->setModel(tmp_chantier.trier_id1());
         playaudio();
     }
    }
 if(arg1=="Surface")
    {
     if (ui->radioButton_7->isChecked())
     {
         ui->tabchantier->setModel(tmp_chantier.trier_id2());
         playaudio();
     }
     if (ui->radioButton_8->isChecked())
     {
         ui->tabchantier->setModel(tmp_chantier.trier_id3());
         playaudio();
     }
    }
 if(arg1=="Budget")
    {
     if (ui->radioButton_7->isChecked())
     {
         ui->tabchantier->setModel(tmp_chantier.trier_id4());
         playaudio();
     }
     if (ui->radioButton_8->isChecked())
     {
         ui->tabchantier->setModel(tmp_chantier.trier_id5());
         playaudio();
     }
    }
 if(arg1=="Date limite")
    {
     if (ui->radioButton_7->isChecked())
     {
         ui->tabchantier->setModel(tmp_chantier.trier_id6());
         playaudio();
     }
     if (ui->radioButton_8->isChecked())
     {
         ui->tabchantier->setModel(tmp_chantier.trier_id7());
         playaudio();
     }
    }
}

void MainWindow::on_comboBox_4_activated(const QString &arg1)
{
    if(arg1=="Nom")
       {
        if (ui->radioButton_13->isChecked())
        {
            ui->tabcha->setModel(tmp_inter.trier1());
            playaudio();
        }
        if (ui->radioButton_12->isChecked())
        {
            ui->tabcha->setModel(tmp_inter.trier2());
            playaudio();
        }
       }
    if(arg1=="Prénom")
       {
        if (ui->radioButton_13->isChecked())
        {
            ui->tabcha->setModel(tmp_inter.trier3());
            playaudio();
        }
        if (ui->radioButton_12->isChecked())
        {
            ui->tabcha->setModel(tmp_inter.trier4());
            playaudio();
        }
       }
}



void MainWindow::on_comboBox_5_activated(const QString &)
{

playaudio();

}

void MainWindow::on_pushButton_3_clicked()
{

playaudio();
    ui->lineEditadres_4->clear();
        ui->lineEditsurface_4->clear();
         ui->lineEditbudget_4->clear();
         ui->lineEdit_6->clear();

}





void MainWindow::on_pushButton_7_clicked()
{
    playaudio();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
     ui->lineEdit_5->clear();
}

void MainWindow::on_pushButton_8_clicked()
{
    playaudio();
    ui->lineeditid->clear();
    ui->lineEditadres->clear();
    ui->lineEditsurface->clear();
    ui->lineEditbudget->clear();
    ui->dateEdit->clear();
}

void MainWindow::on_pushButton_9_clicked()
{
    playaudio();
    ui->ad_chmo->clear();
    ui->sur_chmo->clear();
    ui->bud_chmo->clear();
    ui->date_chmo->clear();
}

void MainWindow::on_pushButton_10_clicked()
{
    playaudio();
    ui->stackedWidget->setCurrentIndex(2);

}


void MainWindow::on_pushButton_11_clicked()
{



QMediaPlayer * music =new QMediaPlayer();
music->setMedia(QUrl("qrc:/images/Flash instant, printer, printing sound effect (128 kbps).mp3"));







        QString num1 = ui->lineEdit_7->text();
        int num = ui->lineEdit_7->text().toInt();

        QSqlQuery query;

        QString id;
        QString adr;
        QString surfa;
        QString bdget,datemil1;
        QDate datemil;

        if(num1!=""){playaudio();

        query.prepare("select * from chantier where ID_CHANTIER =:id_chantier");
        query.bindValue(":id_chantier", num);
        if (query.exec())
        {

            while (query.next()) {

                 id= query.value(0).toString();
                 adr= query.value(1).toString();
                 surfa=query.value(2).toString();
                 bdget=query.value(3).toString();
                 datemil = query.value(4).toDate();
                 datemil1=datemil.toString("dd-MM-yyyy");


             }
        }
              QPrinter printer(QPrinter::HighResolution);
                  printer.setPageSize(QPrinter::A4);
QGraphicsView a;

                 QPrintDialog *dialog = new QPrintDialog(&printer);
                  if (dialog->exec() == QDialog::Accepted)
                  {               QPainter painter(&printer);
                                  painter.begin(&printer);
                                  int iYPos = 0;
                                  int iWidth = printer.width();
                                  int iHeight = printer.height();
                                  QPixmap pxPic;
                                  pxPic.load(":/images/background.jpg","JPG");
                                 QSize s(iWidth/1, iHeight/1);
                                  QPixmap pxScaledPic = pxPic.scaled(s, Qt::IgnoreAspectRatio, Qt::FastTransformation);
                                  painter.drawPixmap(0, iYPos, pxScaledPic.width(), pxScaledPic.height(), pxScaledPic);
                                  iYPos += pxScaledPic.height() + 250;
                                  QFont f;
                                      f.setPointSize(20);
                                      f.setBold(true);
                                      painter.setFont(f);
                                   painter.drawText(1800, 500, "CHANTIER");
                                   f.setPointSize(15);
                                   f.setBold(true);
                                   painter.setFont(f);
                                   painter.drawText(100, 1000, "ID de chantier :");
                                   painter.drawText(1900, 1000,id);
                                   painter.drawText(100, 1300, "Aderesse :");
                                   painter.drawText(1900, 1300,adr);
                                   painter.drawText(100, 1600, "Surface de terrain en m² :");
                                   painter.drawText(1900, 1600,surfa);
                                   painter.drawText(100, 1900, "Budget en dt :");
                                   painter.drawText(1900, 1900,bdget);
                                   painter.drawText(100, 2200, "Date limite :");
                                   painter.drawText(1900, 2200,datemil1);




                                  painter.end();
                                  music->play();


                  }
        }
        else
        {playaudio();
            QMessageBox::critical(nullptr, QObject::tr("Imprimer chantier"),
                        QObject::tr("Erreur !.\n"
                                    "Veuillez selectionner un id d'un chantier à imprimer .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_12_clicked()
{
    int i=ui->lineeditid_2->text().toInt();
    QString p=ui->lineEditadres_2->text();
    int k=ui->lineEditsurface_2->text().toInt();
    QString s=ui->comboBox_3->currentText();

    parking c(i,p,k,s);


    if ((i!='\0')&&(p!='\0')&&(k!='\0'))
    {

    bool test = c.ajouter();
    if(test)

    {
        display_listes();
        playaudio();
        notification n;
        n.ajoutpark();}
else
     {QMessageBox::warning(nullptr,("Ajout parking"),("parking non ajouté"));}
    }

    else QMessageBox::warning(nullptr,("Ajout parking"),("pas de données"));
}

void MainWindow::on_pushButton_13_clicked()
{
    playaudio();
   ui->lineeditid_2->clear();
   ui->lineEditadres_2->clear();
   ui->lineEditsurface_2->clear();
}

void MainWindow::on_modifierchantier_6_clicked()
{
    int i=ui->comboBox_6->currentText().toInt();
    QString p=ui->lineEditadres_5->text();
    int l=ui->lineEditsurface_5->text().toInt();
    QString s=ui->comboBox_5->currentText();

    parking c(i,p,l,s);
    bool test=c.modifier();
    if(test)
    {    playaudio();
         display_listes();
        QMessageBox::information(nullptr, QObject::tr("Modifier un parking"),
                    QObject::tr("un parking a été modifier.\n"
                                "Cliquez sur Ok pour continuer."), QMessageBox::Ok);
    }
    else

       QMessageBox::critical(nullptr, QObject::tr("Modifier un parking"),
                   QObject::tr("Erreur!\n"
                               "Erreur de modification .\n Veuillez réessayer."), QMessageBox::Ok);
}

void MainWindow::on_pushButton_21_clicked()
{
    playaudio();
    ui->comboBox_6->clear();
    ui->lineEditadres_5->clear();
    ui->lineEditsurface_5->clear();
}

void MainWindow::on_supprimerchantier_5_clicked()
{
    int a=ui->lineEdit_24->text().toInt();
   bool test=tmp_parking.supprimer(a);
   if (a!='\0'){
QMessageBox::StandardButton reponse = QMessageBox::question(this,"suppression","confirmer la suppression",QMessageBox::Yes | QMessageBox::No);
if (reponse == QMessageBox::Yes)
{

    if(test)
    {
        playaudio();
        display_listes();
        QMessageBox::information(nullptr, QObject::tr("Supprimer un parking"),
                    QObject::tr("parking supprimé.\n"
                                "Click Ok to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un parking"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    playaudio();}

}
else  return;}

}

void MainWindow::on_pb_ok1_5_clicked()
{
    if (ui->radioButton_21->isChecked())
    {
        QString type= ui->lineEdit_22->text() ;
        ui->tabcha_2->setModel(tmp_parking.chercheradresse(type));
        playaudio();
    }

    if (ui->radioButton_22->isChecked())
    {
        QString type= ui->lineEdit_22->text() ;
        ui->tabcha_2->setModel(tmp_parking.chercherid(type));
        playaudio();
    }


    if (!(ui->radioButton_21->isChecked())&&!(ui->radioButton_22->isChecked()))
           { playaudio();
        QMessageBox::critical(nullptr, QObject::tr("cherche échoué"),
                               QObject::tr("aaaaa\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_comboBox_7_activated(const QString &arg1)
{
   /* if(arg1=="ID")
       {
        if (ui->radioButton_24->isChecked())
        {
            ui->tabcha_2->setModel(tmp_parking.trier_3());
            playaudio();
        }
        if (ui->radioButton_25->isChecked())
        {
            ui->tabcha_2->setModel(tmp_parking.trier_4());
            playaudio();
        }
       }
    if(arg1=="Nombre de places de parking")
       {
        if (ui->radioButton_24->isChecked())
        {
            ui->tabcha_2->setModel(tmp_parking.trier_1());
            playaudio();
        }
        if (ui->radioButton_25->isChecked())
        {
            ui->tabcha_2->setModel(tmp_parking.trier_2());
            playaudio();
        }
       }*/
}

void MainWindow::on_pushButton_22_toggled(bool checked)
{
    if (checked){
        ui->pushButton_22->setIcon((QIcon(":/images/refresh2.png")));
        ui->pushButton_22->setIconSize(ui->pushButton_22->size());
        display_listes();
        ui->lineEdit_24->clear();
        ui->lineEdit_22->clear();
        playaudio();

    }
   else  {
        ui->pushButton_22->setIcon((QIcon(":/images/refresh1.png")));
        ui->pushButton_22->setIconSize(ui->pushButton_22->size());
        display_listes();
        ui->lineEdit_24->clear();
        ui->lineEdit_22->clear();
        playaudio();
}
}

void MainWindow::on_tabcha_2_activated(const QModelIndex &index)
{

    QString a=ui->tabcha_2->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from parking where ID=:id");
    query.bindValue(":id", a);

    if (query.exec())
    {

        while (query.next()) {
            playaudio();
            ui->lineEdit_24->setText(query.value(0).toString());
            ui->comboBox_6->setCurrentText(query.value(0).toString());
            ui->lineEditadres_5->setText(query.value(1).toString());
            ui->lineEditsurface_5->setText(query.value(2).toString());



        }
    }
}


void MainWindow::on_comboBox_stat_type_currentTextChanged()
{

      /*  mainLayout=new QVBoxLayout ;
        mainLayout->addWidget(s.Preparechart(ui->comboBox12->currentText()));
        ui->widget->setLayout(mainLayout);*/
}
void MainWindow::on_comboBox_6_activated(const QString &)
{
    QString a=ui->comboBox_6->currentText();
     QSqlQuery query;
     query.prepare("select * from parking where ID=:id");
     query.bindValue(":id", a);

     if (query.exec())
     {

         while (query.next()) {


              playaudio();

              ui->comboBox_6->setCurrentText(query.value(0).toString());
              ui->lineEditadres_5->setText(query.value(1).toString());
              ui->lineEditsurface_5->setText(query.value(2).toString());
              ui->comboBox_5->setCurrentText(query.value(3).toString());


         }
     }
}
//************************mariem**********************************
//**************************************************************
//****************************************************************

bool MainWindow::verifier_formulaire_ajout_employe(){//condition d'ajout


    if ((ui->lineEditid->text()!="")&&(ui->lineEditnom->text()!="")&&(ui->lineEditprenom->text()!="")&&(ui->lineEdittelephone->text()!="")&&(ui->dateEditddn->text()!="")){
        return true;
    }
    else return false;
}

bool MainWindow::verifier_formulaire_ajout_poste(){


    if ((ui->lineEditid_5->text()!="")&&(ui->lineEditgrade->text()!="")&&(ui->lineEditavantage->text()!="")&&(ui->lineEdithoraire->text()!="")&&(ui->lineEditsalaire->text()!="")){
        return true;
    }
    else return false;
}


void MainWindow::initialiser_formulaire(){

    /*ui->lineEditid->clear();
    ui->lineEditnom->clear();
    ui->lineEditprenom->clear();
    ui->comboBox_post->clear();
    ui->lineEdittelephone->clear();
    ui->dateEditddn->clear();

    ui->comboBox_5->clear();
    ui->lineEditadres_2->clear();
    ui->lineEditprenom_2->clear();
    ui->lineEdittel->clear();
    ui->dateEdit_2->clear();

    ui->lineEditid_5->clear();
    ui->lineEditgrade->clear();
    ui->lineEditavantage->clear();
    ui->lineEdithoraire->clear();
    ui->lineEditsalaire->clear();

    ui->comboBox_4->clear();
    ui->lineEditadres_3->clear();
    ui->lineEditsurface_4->clear();
    ui->lineEditbudget_4->clear();
    ui->lineEditbudget_5->clear();*/

}

void MainWindow::refresh(){
    ui->tableViewEmploye->setModel(tmpemploye.afficher());
    ui->tableViewposte->setModel(tmpposte.afficher());
    ui->comboBox_12->setModel(tmpposte.afficherid());
    ui->comboBox_8->setModel(tmpemploye.afficherid());

     ui->comboBox_post->setModel(tmpposte.affichergrade());
     ui->comboBox_10->setModel(tmpposte.affichergrade());

    ui->comboBox_9->setModel(tmpemploye.afficherid());
    initialiser_formulaire();

}
void MainWindow::on_pushButton_14_clicked()
{
    QString id=ui->lineEditid->text();
    QString nom=ui->lineEditnom->text();
    QString prenom=ui->lineEditprenom->text();
    QString post = ui->comboBox_post->currentText();
    QString telephone=ui->lineEdittelephone->text();
    QString date=ui->dateEditddn->text();

    qDebug()<<verifier_formulaire_ajout_employe();


    if (verifier_formulaire_ajout_employe()==true){
        Employe e(id,nom,prenom,post,telephone,date);

        bool test= e.ajouter();
        notification n;
        n.notification_employe();
        refresh();
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un employe"),
                    QObject::tr("Erreur !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    QString id = ui->comboBox_9->currentText();
    QVector <QString> information=tmpemploye.getinforamation(id);


    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("employe")
        <<  "</head>\n"
        "<body  bgcolor=#ffffff link=#5000A0>\n";
            out << "<h1 style='color: red;text-align: center;'>Fiche de Paie </h1>";
            out << "<span style='text-align: center; display: inline;'><h2>nom:"<<QString("  %1 </h2></span>").arg(information.at(0));
            out << "<span style='text-align: center;'><h2>prenom:</h2>" <<QString("<h3>%1</p></h3>").arg(information.at(1));
            out << "<span style='text-align: center;'><h2>grade:</h2>" <<QString("<h3>%1</p></h3>").arg(information.at(2));
            out << "<span style='text-align: center;'><h2>salaire:</h2>" <<QString("<h3>%1</p></h3>").arg(information.at(3));

        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer(QPrinter::HighResolution);
                printer.setPageSize(QPrinter::A4);
                QPrintDialog *dialog = new QPrintDialog(&printer,this);
                 if (dialog->exec() == QDialog::Accepted)
                    {
                        QPainter painter(&printer);
                        painter.begin(&printer);
                        quint32 iYPos = 0;
                        quint32 iWidth = printer.width();
                        quint32 iHeight = printer.height();
                        QPixmap pxPic,pxPic2,pxPic3;
                        pxPic.load("://perso.png", "PNG");
                        pxPic2.load("://Maryam.jpg", "JPG");
                        pxPic3.load("://signature.png", "PNG");

                        const QImage image2("://Maryam.jpg");
                         const QPoint imageCoordinates(3500,6000);

                         const QImage image3("://signature.png");
                          const QPoint imageCoordinates2(3500,5800);

                        QSize s(iWidth/3, iHeight/5);
                        QPixmap pxScaledPic = pxPic.scaled(s, Qt::KeepAspectRatio, Qt::FastTransformation);
                        painter.drawPixmap(3500, iYPos, pxScaledPic.width(), pxScaledPic.height(), pxScaledPic);
                        iYPos -= pxScaledPic.height() + 1000;



                        QFont f;
                        f.setPointSize(20);
                        f.setBold(true);
                        f.setItalic(true);
                        painter.setBrush(QColor(50,205,50));
                        painter.setFont(f);
                        painter.drawText(1700,400,"fiche de paie");
                        painter.drawText(100, 1000, "Nom:");
                        painter.drawText(1000, 1000,information.at(0));
                        painter.drawText(100, 1400, "Prenom: ");
                        painter.drawText(1000, 1400,information.at(0));
                        painter.drawText(100, 1700, "Poste: ");
                        painter.drawText(1000, 1700,information.at(2));
                        painter.drawText(100, 2000, "Salaire: ");
                        painter.drawText(1000, 2000,information.at(3));
                        painter.drawText(1500, 2000, "DT ");

                        painter.drawImage(imageCoordinates, image2);
                        painter.drawImage(imageCoordinates2, image3);

                        //pxPic.load("C:/Users/MEGA-PC/Downloads/mohsen/mariem/projet/perso.png", "PNG");
                       }
}

void MainWindow::on_supprimeremploye_clicked()
{
    QString ide=ui->lineEdit_21->text();

    Employe e;

    bool test= e.supprimer(ide);
    refresh();
    if (test==1){
        QMessageBox::information(nullptr, QObject::tr("supprimer employe"),
                          QObject::tr("employe supprime.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }else{
        QMessageBox::critical(nullptr, QObject::tr("supprimer employe"),
                    QObject::tr("Erreur !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_pushButton_18_clicked()
{
    QString id=ui->lineEditid_5->text();
    QString grade=ui->lineEditgrade->text();
    QString avantage=ui->lineEditavantage->text();
    QString horaire = ui->lineEdithoraire->text();
    QString salaire=ui->lineEditsalaire->text();
    if(verifier_formulaire_ajout_poste()){
         poste p(id,grade,avantage,horaire,salaire);
         bool test= p.ajouter();
         notification n;
         n.notification_poste();
         refresh();
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter poste"),
                    QObject::tr("Erreur !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_supprimerposte_2_clicked()
{
    QString idp=ui->lineEdit_26->text();

    poste p;

    bool test= p.supprimer(idp);
    refresh();
    if (test==1){
        QMessageBox::information(nullptr, QObject::tr("Supprimer Poste"),
                          QObject::tr("poste supprime.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Poste"),
                    QObject::tr("Erreur !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifierchantier_4_clicked()
{
    QString id=ui->comboBox_12->currentText();
    QString grade=ui->lineEditadres_6->text();
    QString avantage=ui->lineEditsurface_6->text();
    QString horaire = ui->lineEditbudget_5->text();
    QString salaire=ui->lineEditbudget_6->text();

    poste p (id,grade,avantage,horaire,salaire);

    bool test= p.modifier(id);
     refresh();
     if (test==1){
         QMessageBox::information(nullptr, QObject::tr("Modifier Poste"),
                           QObject::tr("poste modifié.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
     }else{
         QMessageBox::critical(nullptr, QObject::tr("modifier Poste"),
                     QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
     }
}

void MainWindow::on_modifierchantier_2_clicked()
{
    QString id=ui->comboBox_8->currentText();
    QString nom=ui->lineEditadres_3->text();
    QString prenom= ui->lineEditprenom_2->text();
    QString poste=ui->comboBox_10->currentText();
    QString telephone=ui->lineEdittel->text();
    QString date=ui->dateEdit_2->text();

    Employe e (id,nom, prenom,poste,telephone,date);
    bool test= e.modifier(id);
    refresh();

    if (test==1){
        QMessageBox::information(nullptr, QObject::tr("Ajouter Poste"),
                          QObject::tr("employe modifier.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter Poste"),
                    QObject::tr("Erreur !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_ok1_3_clicked()
{
    ui->tableViewEmploye->setModel(tmpemploye.recherche_id(ui->lineEdit_20->text()));
}

void MainWindow::on_pb_ok1_4_clicked()
{
    ui->tableViewposte->setModel(tmpposte.recherche(ui->lineEdit_25->text()));
}

void MainWindow::on_comboBox_13_activated(const QString &arg1)
{
    QString mode="DESC";
    if (ui->checkBox_2->checkState()==false)
        mode="ASC";
    ui->tableViewposte->setModel(tmpposte.trier(ui->comboBox_13->currentText(),mode));
}

void MainWindow::on_checkBox_2_clicked()
{
    QString mode="DESC";
    if (ui->checkBox_2->checkState()==false)
        mode="ASC";
    ui->tableViewposte->setModel(tmpposte.trier(ui->comboBox_13->currentText(),mode));
}

void MainWindow::on_comboBox_11_activated(const QString &arg1)
{

        QString mode="DESC";
        if (ui->checkBox->checkState()==false)
            mode="ASC";
        ui->tableViewEmploye->setModel(tmpemploye.trier(ui->comboBox_11->currentText(),mode));

}

void MainWindow::on_checkBox_clicked()
{
    QString mode="DESC";
    if (ui->checkBox->checkState()==false)
        mode="ASC";
    ui->tableViewEmploye->setModel(tmpemploye.trier(ui->comboBox_11->currentText(),mode));
}

void MainWindow::on_comboBox_12_activated(const QString &arg1)
{
    QString id=ui->comboBox_12->currentText();
    QSqlQuery * query=tmpposte.recherche_id(id);
    QString grade;
    QString avantage;
    QString horaire;
    QString salaire;

    if (query->next())
      {
        grade= query->value(1).toString();
        ui->lineEditadres_6->setText(grade);
        avantage= query->value(2).toString();
        ui->lineEditsurface_6->setText(avantage);
        horaire= query->value(3).toString();
        ui->lineEditbudget_5->setText(horaire);
        salaire= query->value(4).toString();
        ui->lineEditbudget_6->setText(salaire);
      }
}

void MainWindow::on_comboBox_8_activated(const QString &arg1)
{
    QString id=ui->comboBox_8->currentText();
    QSqlQuery * query=tmpemploye.recherche_id2(id);
    QString nom;
    QString prenom;
    QString poste;
    QString telephone;


    if (query->next())
      {
        nom= query->value(1).toString();
        ui->lineEditadres_3->setText(nom);
        prenom= query->value(2).toString();
        ui->lineEditprenom_2->setText(prenom);
        poste= query->value(3).toString();
        ui->comboBox_10->setCurrentText(poste);
        telephone= query->value(4).toString();
        ui->lineEdittel->setText(telephone);
      }
}

void MainWindow::on_pushButton_16_clicked()
{
    int i= ui->verticalLayout_3->count();
     if (i==1){
         delete ui->verticalLayout_3->itemAt(0)->widget();
         ui->verticalLayout_3->addWidget(tmpemploye.statistique());
     }else{
         ui->verticalLayout_3->addWidget(tmpemploye.statistique());
     }
}

void MainWindow::on_pushButton_17_clicked()
{
   int i= ui->verticalLayout_8->count();
     if (i==1){
         delete ui->verticalLayout_8->itemAt(0)->widget();
         ui->verticalLayout_8->addWidget(tmpemploye.statistique2());
     }else{
         ui->verticalLayout_8->addWidget(tmpemploye.statistique2());
     }
}

//**********************mahdi********************
//*********************************************
//******************************************

void MainWindow::on_pushButton_19_clicked()
{
    int a=ui->lineEdit1->text().toInt();
    QString b=ui->lineEdit2->text();
    QString c=ui->lineEdit3->text();
    int d=ui->lineEdit4->text().toInt();
    QString e=ui->lineEdit5->text();

    fournisseur f(a,b,c,d,e);

       if ((a!='\0')&&(b!='\0')&&(c!='\0')&&(d!='\0')&&(e!='\0'))
       {

       bool test = f.ajouter();
       if(test)

       {
           notification n;
           n.notification_fourni();
           ui->tableView->setModel(f.afficher());
       }
   else
       {QMessageBox::warning(nullptr,("Ajout fournisseur"),("fournisseur non ajouter"));
       }
       }
       else QMessageBox::warning(nullptr,("Ajout fournisseur"),("pas de données"));
}

void MainWindow::on_comboBox_15_activated(const QString &arg1)
{
    // ui->tableView->setModel(f.tri_nom());
     //qDebug()<<arg1;
         if(arg1=="ID")
            {
                 ui->tableView->setModel(f.tri_id());
            }

         if(arg1=="Nom")
            {
                 ui->tableView->setModel(f.tri_nom());
            }

         if(arg1=="type")
            {
                 ui->tableView->setModel(f.tri_type());
            }
         if(arg1=="numero")
                    {
                         ui->tableView->setModel(f.tri_numero());
                    }
         if(arg1=="adresse")
            {
                 ui->tableView->setModel(f.tri_adresse());
            }
}

void MainWindow::on_pb_ok1_6_clicked()
{
    QString a= ui->lineEdit_28->text();
    ui->tableView->setModel(f.recherche_id(a));
}

void MainWindow::on_modifier_clicked()
{
    int a=ui->comboBox_14->currentText().toInt();
    QString b=ui->lineEdit_27->text();
    QString c=ui->lineEdit_33->text();
    int d=ui->lineEdit_44->text().toInt();
    QString e=ui->lineEdit_55->text();

    fournisseur f(a,b,c,d,e);

    //   if ((a!='\0')&&(b!='\0')&&(c!='\0')&&(d!='\0')&&(e!='\0'))
       {

       bool test = f.modifier();
       if(test)

       {
           QMessageBox::information(nullptr,("modifier fournisseur"),("fournisseur modifié"));
           ui->tableView->setModel(f.afficher());
       }
   else
       {QMessageBox::warning(nullptr,("modifier fournisseur"),("fournisseur non modifier"));
       }
       }
//       else QMessageBox::warning(nullptr,("modifier fournisseur"),("pas de données"));
}

void MainWindow::on_supprimer_clicked()
{
    int a=ui->lineEdit_sup->text().toInt();
     bool test=f.supprimer(a);
     if (a!='\0'){
    QMessageBox::StandardButton supprimer = QMessageBox::question(this,"suppression","confirmer la suppression !!!",QMessageBox::Yes|QMessageBox::No);
     if (supprimer == QMessageBox::Yes)  {
         if(test){

                 QMessageBox::information(nullptr, QObject::tr("Supprimer un fournisseur"),
                              QObject::tr("fournisseur supprimé.\n"
                                          "Click OK to exit."), QMessageBox::Cancel);
            }
            else
                QMessageBox::critical(nullptr, QObject::tr("supprimer un fournisseur"),
                            QObject::tr("Erreur !.\n"
                                        "Veuillez saisir un idCon pour supprimer un fournisseur .\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
 }
   else return;
 }
}

void MainWindow::on_pushButton_23_clicked()
{
    QString a1=ui->lineEdit_e1->text();
    QString b2=ui->lineEdit_e2->text();
    int c3=ui->lineEdit_e3->text().toInt();
    QDate d3=ui->dateEdit_3->date();
    float e4=ui->lineEdit_e4->text().toFloat();

    equipements e1(a1,b2,c3,d3,e4);

       if ((a1!='\0')&&(b2!='\0')&&(c3!='\0')&&(e4!='\0'))
       {

       bool test = e1.ajouter();
       if(test)

       {
           notification n;
           n.notification_equi();
           ui->tableView_2->setModel(e1.afficher());
       }
   else
       {QMessageBox::warning(nullptr,("Ajout equipement"),("equipement non ajouter"));
       }
       }
        else QMessageBox::warning(nullptr,("Ajout equipement"),("pas de données"));
}

void MainWindow::on_comboBox_17_activated(const QString &arg1)
{
    // qDebug()<<arg1;
     if(arg1=="Code")
        {
             ui->tableView_2->setModel(e1.tri_code());
        }

     if(arg1=="Quantite")
        {
             ui->tableView_2->setModel(e1.tri_quantite());
        }

     if(arg1=="Description")
        {
             ui->tableView_2->setModel(e1.tri_description());
        }

     if(arg1=="Date")
        {
             ui->tableView_2->setModel(e1.tri_date());
        }

     if(arg1=="Prix")
        {
             ui->tableView_2->setModel(e1.tri_prix());
        }
}

void MainWindow::on_chercher_equi_clicked()
{
    QString a1= ui->lineEdit_29->text() ;
    ui->tableView_2->setModel(e1.recherche_code(a1));
}

void MainWindow::on_modifier_equi_clicked()
{
    QString a1=ui->comboBox_16->currentText();
    QString b2=ui->lineEdit_e22->text();
    int c3=ui->lineEdit_e33->text().toInt();
    QDate d3=ui->dateEdit_e2->date();
    float e4=ui->lineEdit_e44->text().toFloat();

  equipements e1(a1,b2,c3,d3,e4);
       {
       bool test = e1.modifier();
       if(test)

       {
           QMessageBox::information(nullptr,("modifier equipement"),("equipement modifié"));
           ui->tableView_2->setModel(e1.afficher());
       }
   else
       {QMessageBox::warning(nullptr,("Amodifier equipement"),("equipement non modifié"));
       }
       }
}

void MainWindow::on_supprimer_equi_clicked()
{
    QString a1=ui->lineEdit_supp->text();
       bool test=e1.supprimer(a1);
       if (a1!='\0'){
      QMessageBox::StandardButton supprimer_equi = QMessageBox::question(this,"suppression","confirmer la suppression !!!",QMessageBox::Yes|QMessageBox::No);
       if (supprimer_equi == QMessageBox::Yes)  {
           if(test)

                    QMessageBox::information(nullptr, QObject::tr("Supprimer un equipement"),
                                QObject::tr("equipement supprimé.\n"
                                            "Click OK to exit."), QMessageBox::Cancel);
              }
              else
                  QMessageBox::critical(nullptr, QObject::tr("supprimer un equipement"),
                              QObject::tr("Erreur !.\n"
                                          "Veuillez saisir un idCon pour supprimer un equipement .\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

   }
}

void MainWindow::on_comboBox_14_activated(const QString &arg1)
{
    QString a=ui->comboBox_14->currentText();
          QSqlQuery query;
          query.prepare("select * from fournisseur where id =:id");
          query.bindValue(":id", a);

          if (query.exec())
          {

              while (query.next()) {

                   ui->comboBox_14->setCurrentText(query.value(0).toString());
                   ui->lineEdit_27->setText(query.value(1).toString());
                   ui->lineEdit_33->setText(query.value(2).toString());
                   ui->lineEdit_44->setText(query.value(3).toString());
                   ui->lineEdit_55->setText(query.value(4).toString());

              }
          }
}

void MainWindow::on_comboBox_16_activated(const QString &arg1)
{
    QString a1=ui->comboBox_16->currentText();
          QSqlQuery query;
          query.prepare("select * from equipements where code =:code");
          query.bindValue(":code", a1);

          if (query.exec())
          {

              while (query.next()) {

                   ui->comboBox_16->setCurrentText(query.value(0).toString());
                   ui->lineEdit_e22->setText(query.value(1).toString());
                   ui->lineEdit_e33->setText(query.value(2).toString());
                   ui->dateEdit_e2->setDate(query.value(3).toDate());
                   ui->lineEdit_e44->setText(query.value(4).toString());

              }
          }
}

void MainWindow::on_tabWidget_11_tabBarClicked(int index)
{
    QPieSeries *series= new QPieSeries();
      QSqlQuery query;
      query.prepare("select description, quantite from equipements;");
      QVector<int> q;
      QVector<QString> vectdesc;
      if(query.exec()){
          while(query.next()){
          vectdesc.push_back(query.value(0).toString());
          q.push_back(query.value(1).toInt());
            }

       int s=0;
       for (int i=0;i<q.size();i++) s+=q[i];

       for (int i=0;i<vectdesc.size();i++){
      series->append(vectdesc[i], (qreal)((qreal)q[i]/(qreal)s)*100.0);

         }
      QChart *ch= new QChart();
      ch->addSeries(series);
      ch->setTitle(QString("statistique des quantitées de la table equipements par rapport au description"));
      ch->legend()->show();
      ch->setAnimationOptions(QChart::AllAnimations);
      QChartView *chart=new QChartView(ch);
      chart->setRenderHint(QPainter::Antialiasing);//graphique
      chart->setGeometry(ui->graphicsView_22->geometry());//taille de la page
      QGridLayout q;
      q.addWidget(chart);
      ui->graphicsView_22->setLayout(&q);
      }
}

void MainWindow::refreshma(){
ui->tableView->setModel(f.afficher());
ui->tableView_2->setModel(e1.afficher());
ui->comboBox_14->setModel(f.combo_box());
ui->comboBox_16->setModel(e1.combo_box());
}
void MainWindow::on_pushButton_20_clicked()
{
    refreshma();
}

void MainWindow::on_actualiser_clicked()
{
    refreshma();
}

void MainWindow::on_connexion_4_clicked()
{
    QString a,b;
    QSqlQuery query;
    query.prepare("select pse,mdp from login ");
    query.exec();
    while(query.next())
    {
    a =query.value(0).toString();
    b =query.value(0).toString();
    }
    if((ui->pseudo_4->text()==a) && (ui->mdp_4->text()==b))
    {
            QMessageBox::information(nullptr, QObject::tr("Se connecter"),
                        QObject::tr("Connexion réussie.\n"
                                    "Cliquez sur ok pour continuer."), QMessageBox::Ok);
            ui->stackedWidget->setCurrentIndex(1);
            display_listes();
            refresh();
            refreshma();
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Se connecter"),
                    QObject::tr("La connexion a échoué.\n"
                                "Veuillez réessayer."), QMessageBox::Cancel);
    }


}

void MainWindow::on_pushButton_envoyer_clicked()
{
    playaudio();
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);




                smtp.setUser("smartmunicipality40@gmail.com");
                smtp.setPassword("municipality");



        MimeMessage message;

        message.setSender(new EmailAddress("smartmunicipality40@gmail.com", "ARIANA municipality"));
        message.addRecipient(new EmailAddress(ui->lineEdit_adresse->text(), "Recipient's name"));
        message.setSubject(ui->lineEdit_objet->text());



        MimeText text;

        text.setText(ui->textEdit_texte->toPlainText());



        message.addPart(&text);


        smtp.connectToHost();
        smtp.login();
        if (smtp.sendMail(message)){
           QMessageBox::information(this, "OK", "email envoyé");
        }
        else{
           QMessageBox::critical(this, "Erreur","email non envoyé");
        }
        smtp.quit();

}

void MainWindow::on_pushButton_envoyer_2_clicked()
{
    playaudio();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_comboBox_18_activated(const QString &)
{
    QString a=ui->comboBox_18->currentText();
     QSqlQuery query;
     query.prepare("select * from inter where email=:email");
     query.bindValue(":email", a);

     if (query.exec())
     {

         while (query.next()) {


              playaudio();
              ui->lineEdit_adresse->setText(query.value(4).toString());


         }
     }
}

void MainWindow::on_pushButton_24_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_envoyer_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_envoyer_4_clicked()
{
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);




                smtp.setUser("smartmunicipality40@gmail.com");
                smtp.setPassword("municipality");



        MimeMessage message;

        message.setSender(new EmailAddress("smartmunicipality40@gmail.com", "ARIANA municipality"));
        message.addRecipient(new EmailAddress(ui->lineEdit_adresse_2->text(), "Recipient's name"));
        message.setSubject(ui->lineEdit_objet_2->text());



        MimeText text;

        text.setText(ui->textEdit_texte_2->toPlainText());



        message.addPart(&text);


        smtp.connectToHost();
        smtp.login();
        if (smtp.sendMail(message)){
           QMessageBox::information(this, "OK", "email envoyé");
        }
        else{
           QMessageBox::critical(this, "Erreur","email non envoyé");
        }
        smtp.quit();
}

void MainWindow::on_pushButton_25_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
