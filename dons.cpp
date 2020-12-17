#include "dons.h"
#include "mainwindow.h"
#include "QSqlQueryModel"

don::don(){
    donateur="";

    montant=0;}



don::don(QString donateur ,QDate date_don, float montant)
{
    this->donateur=donateur;
    this->date_don=date_don;
    this->montant=montant;
}

bool don::ajouter(){
    QSqlQuery query;
    QString b ;
    b.setNum(montant);
    query.prepare("INSERT INTO dons(donateur,date_don,montant) VALUES(:donateur , :date_don ,:montant)");

    query.bindValue(":donateur", donateur);
    query.bindValue(":date_don", date_don);
    query.bindValue(":montant",b);

    return query.exec();
}

  QSqlQueryModel*don::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("Select * from dons");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donateur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_don"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    return model;
}

bool don::supprimer(QString donateur)
{
    QSqlQuery query;
    query.prepare("Delete from dons where donateur = :donateur");
    query.bindValue(":donateur",donateur );
    return query.exec();
}
bool don::modifier(QString donateur,QDate date_don,float montant)
{
    QSqlQuery query;
   QString k ;
           k.setNum(montant);

    query.prepare("UPDATE dons SET donateur=:donateur, date_don=:date_don, montant=:montant where donateur = '" +donateur+"'");
    query.bindValue(":donateur",donateur );
    query.bindValue(":date_don",date_don);
    query.bindValue(":montant",k);


    return query.exec();
}

QSqlQueryModel * don::recherche_donateur(QString donateur){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * From dons WHERE donateur ='" +donateur+"'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donateur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_don"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    return model;
}





QSqlQueryModel * don::tri_montant()
    {

    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select * from dons\
                         Order by montant ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donateur"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_don"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));

    return model;
}






