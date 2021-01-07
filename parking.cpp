#include "parking.h"

parking::parking()
{

}
parking::parking(int id,QString adresse,int nbrpar,QString type)
{
    this->id=id;
    this->adresse=adresse;
    this->nbrpar=nbrpar;
    this->type=type;
}
bool parking::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString res1= QString::number(nbrpar);


    query.prepare("INSERT INTO parking (ID,adresse,nbr,type,res) VALUES (:id,:adresse,:nbr,:type,:res)");
    query.bindValue(":id",res);
    query.bindValue(":adresse",adresse);
    query.bindValue(":nbr",res1);
    query.bindValue(":type",type);
    query.bindValue(":res","0");
    return    query.exec();
}
QSqlQueryModel * parking::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from parking ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de places de parking"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type de parking"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("les places réservés"));


    return model;
}
bool parking::modifier()
{

    QSqlQuery query;
    QString res= QString::number(this->id);
    QString res1= QString::number(this->nbrpar);

    query.prepare("UPDATE parking SET adresse=:adresse,nbr=:nbr,type=:type  WHERE id=:id") ;
    query.bindValue(":id",res);
    query.bindValue(":adresse",adresse);
    query.bindValue(":nbr",res1);
    query.bindValue(":type",type);

    return    query.exec();
}
bool parking::modi(QString a,QString b)
{
    QSqlQuery query;
    query.prepare("UPDATE parking SET res=:res WHERE id=:id");
    query.bindValue(":res",a);
    query.bindValue(":id",b);
    return query.exec();
}

QSqlQueryModel * parking::combo_box(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select ID from parking");
    return model;
}
bool parking::supprimer(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("Delete from parking where ID =:id");
    query.bindValue(":id", res);
    return query.exec();
}
QSqlQueryModel * parking::chercherid(const QString &type)
{
     QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from parking where id like '" + type + "%' ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de places de parking"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type de parking"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("les places réservés"));
    return model;
}
QSqlQueryModel * parking::chercheradresse(const QString &type)
{
     QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from parking where adresse like '" + type + "%' ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de places de parking"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type de parking"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("les places réservés"));
    return model;
}
QSqlQueryModel * parking::trier_1()
{
    QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("SELECT * FROM parking\
                        ORDER BY nbr ");

                      model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
                      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de places de parking"));
                      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type de parking"));
                      model->setHeaderData(4, Qt::Horizontal, QObject::tr("les places réservés"));
      return  model;
}
QSqlQueryModel * parking::trier_2()
{
    QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("SELECT * FROM parking\
                        ORDER BY nbr DESC");

                      model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
                      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de places de parking"));
                      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type de parking"));
                      model->setHeaderData(4, Qt::Horizontal, QObject::tr("les places réservés"));
      return  model;
}
QSqlQueryModel * parking::trier_3()
{
    QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("SELECT * FROM parking\
                        ORDER BY id ");

                      model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
                      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de places de parking"));
                      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type de parking"));
                      model->setHeaderData(4, Qt::Horizontal, QObject::tr("les places réservés"));
      return  model;
}
QSqlQueryModel * parking::trier_4()
{
    QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("SELECT * FROM parking\
                        ORDER BY id DESC");

                      model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
                      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de places de parking"));
                      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type de parking"));
                      model->setHeaderData(4, Qt::Horizontal, QObject::tr("les places réservés"));
      return  model;
}
