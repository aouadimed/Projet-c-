#ifndef DONS_H
#define DONS_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class don
{ private:

    QString donateur;
    QDate date_don;
    float montant;

public:
     don();
    don(QString,QDate,float);

    QString Getdonateur() {return donateur;}
            void Setdonateur(QString x){donateur=x;}
   
    QDate Getdate_don() { return date_don; }
            void Setdate_don(QDate x) { date_don = x; }
    float Getmontant() { return montant; }
            void Setmontant( float x) { montant = x; }
  


            bool ajouter();
            QSqlQueryModel*afficher();
            bool supprimer(QString);
            bool modifier(QString,QDate,float);
            QSqlQueryModel * combo_box();


            QSqlQueryModel * tri_montant();
            QSqlQueryModel * recherche_donateur(QString);



};
#endif // EQUIPEMENTS_H
