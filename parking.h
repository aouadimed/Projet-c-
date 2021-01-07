#ifndef PARKING_H
#define PARKING_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class parking
{

int id,nbrpar;
QString adresse,type;
public:
    parking();
    parking(int,QString,int,QString);
    int getid(){return id;}
    QString getadr(){return adresse;}
    int getnb(){return nbrpar;}
    QString gettype(){return type;}
    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier();
    QSqlQueryModel * combo_box();
    bool supprimer(int);
    QSqlQueryModel * chercherid(const QString &);
    QSqlQueryModel * chercheradresse(const QString &);
    QSqlQueryModel * trier_1();
    QSqlQueryModel * trier_2();
    QSqlQueryModel * trier_3();
    QSqlQueryModel * trier_4();
bool modi(QString,QString);
};

#endif // PARKING_H
