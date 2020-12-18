#ifndef CITOYEN_H
#define CITOYEN_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>



class citoyen
{private:
    QString nom,prenom,CIN;
    QDate date_naissance;

public:
    citoyen();
    citoyen(QString,QString,QString,QDate);

    QString Getnom() {return nom;}
    void Setnom(QString a){nom=a;}

    QString getprenom() {return prenom;}
    void Setprenomnom(QString a){nom=a;}

    QString GetCIN() { return CIN;}
    void SetCIN(QString a){CIN=a;}

    QDate Getdate_naissance(){return  date_naissance;}
    void Setdate_naissance(QDate a) {date_naissance=a;}





};

#endif // CITOYEN_H
