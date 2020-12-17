#include "Ecaritatif.h"
ecaritatif::ecaritatif(){

    lieu="";
    initiateur="";
    responsable="";
}

ecaritatif::ecaritatif( QDate date_eve, QString lieu , QString initiateur , QString responsable)
{
    this->lieu=lieu;
    this->initiateur=initiateur;
    this->responsable=responsable;
    this->date_eve=date_eve;
}

bool ecaritatif::ajouter(){
    QSqlQuery query;


    query.prepare("INSERT INTO ECARITATIF (initiateur,responsable,date_eve,lieu ) VALUES (:initiateur, :responsable ,:date_eve, :lieu)");

    query.bindValue(":responsable", responsable);
    query.bindValue(":initiateur",initiateur);


      query.bindValue(":date_eve", date_eve);

    query.bindValue(":lieu", lieu);



    return query.exec();

}

bool ecaritatif::modifier(QDate date_eve,QString responsable,QString initiateur ,QString lieu)
{
    QSqlQuery query;



    query.prepare("UPDATE ECARITATIF SET  responsable=:responsable, initiateur=:initiateur, date_eve=:date_eve,lieu=:lieu where responsable = '" +responsable+"'");

    query.bindValue(":responsable",responsable);
    query.bindValue(":initiateur", initiateur);
    query.bindValue(":date_eve",date_eve);
    query.bindValue(":lieu",lieu);


    return query.exec();
}

QSqlQueryModel*ecaritatif::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("Select * from ECARITATIF");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("initiateur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("responsable"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_eve"));

    return model;
}

bool ecaritatif::supprimer(QString responsable)
{
    QSqlQuery query;

    query.prepare("Delete from ECARITATIF where responsable = :responsable");
    query.bindValue(":responsable", responsable);
    return query.exec();
}

QSqlQueryModel * ecaritatif::combo_box(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select responsable from ecaritatif");
    return model;
}

QSqlQueryModel * ecaritatif::tri_responsable()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select * from  ECARITATIF\
                         Order by responsable ASC");
                    model->setHeaderData(0, Qt::Horizontal, QObject::tr("initiateur"));
                    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
                    model->setHeaderData(1, Qt::Horizontal, QObject::tr("responsable"));
                    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_eve"));



    return model;
}

QSqlQueryModel * ecaritatif::recherche_responsable(QString responsable){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * From ECARITATIF WHERE responsable = '" +responsable+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("initiateur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("responsable"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_eve"));


    return model;
}

QSqlQueryModel * ecaritatif::recherche_lieu(QString lieu){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * From ECARITATIF WHERE lieu ='" +lieu+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("initiateur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("responsable"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_eve"));



    return model;
}

QSqlQueryModel * ecaritatif::recherche_initiateur(QString){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * From ECARITATIF WHERE initiateur ='" +initiateur+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("initiateur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("responsable"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_eve"));


    return model;
}


