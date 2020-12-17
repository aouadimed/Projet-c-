#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include "Ecaritatif.h"
#include "dons.h"
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setIcon((QIcon(":/images/2.png")));
    ui->pushButton->setIconSize(ui->pushButton->size());

    ui->pushButton_2->setIcon((QIcon(":/images/2.png")));
    ui->pushButton_2->setIconSize(ui->pushButton_2->size());

    ui->pushButton_3->setIcon((QIcon(":/images/pngtree-cartoon-arrow-icon-download-image_1256957.png")));
    ui->pushButton_3->setIconSize(ui->pushButton_3->size());



    ui->pb_ok1->setIcon((QIcon(":/images/4.png")));
    ui->pb_ok1->setIconSize(ui->pb_ok1->size());

    ui->chercher_equi->setIcon((QIcon(":/images/4.png")));
    ui->chercher_equi->setIconSize(ui->chercher_equi->size());

    ui->modifier_equi->setIcon((QIcon(":/images/1.png")));
    ui->modifier_equi->setIconSize(ui->modifier_equi->size());

    ui->supprimer_equi->setIcon((QIcon(":/images/3.png")));
    ui->supprimer_equi->setIconSize(ui->supprimer_equi->size());

    ui->modifier->setIcon((QIcon(":/images/1.png")));
    ui->modifier->setIconSize(ui->modifier->size());

    ui->supprimer->setIcon((QIcon(":/images/3.png")));
    ui->supprimer->setIconSize(ui->supprimer->size());

    ui->actualiser->setIcon((QIcon(":/images/pngtree-cartoon-arrow-icon-download-image_1256957.png")));
    ui->actualiser->setIconSize(ui->actualiser->size());

    ui->tableView->setModel(f.afficher());
    ui->tableView_2->setModel(e.afficher());
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    QString a1=ui->lineEdit_e1->text();
    QString a2=ui->lineEdit_e2->text();
    QString a3=ui->lineEdit->text();
    QDate b2=ui->dateEdit_3->date();

//*qstiring qddat float
 ecaritatif e(b2,a3,a2,a1);

       if ((a1!='\0')&&(a2!='\0')&&(a3!='\0'))
       {

       bool test = e.ajouter();
       if(test)

       {
           QMessageBox::information(nullptr,("Ajout événement caritatif"),("événement caritatif ajouté"));
           ui->tableView_2->setModel(e.afficher());
       }
   else
       {QMessageBox::warning(nullptr,("Ajout événement caritatif"),("événement caritatif non ajouter"));
       }
       }
        else QMessageBox::warning(nullptr,("Ajout événement caritatif"),("pas de données"));
}


void MainWindow::on_pushButton_clicked()
{

    QString b=ui->lineEdit1->text();
 float c=ui->lineEdit3->text().toFloat();
    QDate a=ui->dateEdit->date();


 don  f(b,a,c);

       if ((b!='\0')&&(c!='\0'))
       {

       bool test = f.ajouter();
       if(test)

       {
           QMessageBox::information(nullptr,("Ajout  Don"),("Don ajouté"));
           ui->tableView->setModel(f.afficher());
       }
   else
       {QMessageBox::warning(nullptr,("Ajout  Don"),(" Don non ajouter"));
       }
       }
       else QMessageBox::warning(nullptr,("Ajout  Don"),("pas de données"));
}



void MainWindow::on_modifier_clicked()
{
    QString b=ui->lineEdit_3->text();
     float c=ui->emontant->text().toFloat();
    QDate a=ui->dateEdit_3->date();
    don f(b,a,c);

       if ((b!='\0')&&(c!='\0'))
       {

       bool test = f.modifier(b,a,c);
       if(test)

       {
           QMessageBox::information(nullptr,("Modification Don"),("Don modifié"));
           ui->tableView->setModel(f.afficher());
       }
   else
       {QMessageBox::warning(nullptr,("Modification Don"),("Don non  modifié"));
       }
       }
       else QMessageBox::warning(nullptr,("Modification Don"),("pas de données"));
}

void MainWindow::on_modifier_equi_clicked()
{
    QString a1=ui->l1->text();
    QString a2=ui->l2->text();
    QString a3=ui->l3->text();

    QDate b2=ui->dateEdit_7->date();

    ecaritatif (b2,a3,a2,a1);

       if ((a1!='\0')&&(a2!='\0')&&(a3!='\0'))
       {

       bool test = e.modifier(b2,a2,a1,a3);
       if(test)

       {
           QMessageBox::information(nullptr,("Modification de l'événement caritatif"),("événement caritatif modifié"));
           ui->tableView_2->setModel(e.afficher());
       }
   else
       {QMessageBox::warning(nullptr,("Modification de l'événement caritatif"),("événement caritatif non  modifié"));
       }
       }
        else QMessageBox::warning(nullptr,("Modification de l'événement caritatif"),("pas de données"));
}




void MainWindow::on_pushButton_3_clicked()
{
         ui->tableView->setModel(f.afficher());
}

void MainWindow::on_supprimer_clicked()
{QString a1=ui->lineEdit_19->text();
    f.supprimer(a1);
     ui->tableView->setModel(f.afficher());

}



void MainWindow::on_pb_ok1_clicked()
{ QString a1=ui->lineEdit_18->text();

    ui->tableView->setModel( f.recherche_donateur( a1));
}





void MainWindow::on_supprimer_equi_clicked()
{ QString a1=ui->lineEdit_20->text();
    e.supprimer(a1);
    ui->tableView_2->setModel(e.afficher());

}

void MainWindow::on_chercher_equi_clicked()
{
    QString a1=ui->lineEdit_21->text();

        ui->tableView_2->setModel( e.recherche_responsable( a1));
}

void MainWindow::on_actualiser_clicked()
{
     ui->tableView_2->setModel( e.afficher());
}

void MainWindow::on_pushButton_4_clicked()
{  ui->tableView->setModel(f.tri_montant());

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tableView_2->setModel(e.tri_responsable());
}
