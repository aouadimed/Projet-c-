#ifndef ECARITATIF_H
#define ECARITATIF_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class ecaritatif
{ private:
    QDate date_eve;
    QString lieu,initiateur,responsable;


public:
    ecaritatif();
    ecaritatif(QDate,QString,QString,QString);
    
    QDate Getdate_eve() { return date_eve; }
            void Setdate_eve(QDate x) { date_eve = x; }
    QString Getlieu() {return lieu;}
            void Setlieu(QString x){lieu=x;}
    QString Getinitiateur() {return initiateur;}
            void Setinitiateur(QString x){initiateur=x;}
    QString Getresponsable() {return responsable;}
            void Setresponsable(QString x){responsable=x;}
            

   


            bool ajouter();
            QSqlQueryModel*afficher();
            bool supprimer(QString);
            bool modifier(QDate,QString,QString,QString);
            QSqlQueryModel * combo_box();


            QSqlQueryModel * tri_responsable();
            QSqlQueryModel * recherche_responsable(QString);
            QSqlQueryModel * recherche_lieu(QString);
            QSqlQueryModel * recherche_initiateur(QString);

};

#endif // FOURNISSEUR_H
