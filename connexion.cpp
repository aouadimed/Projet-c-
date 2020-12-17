#include "connexion.h"

connexion::connexion()
{

}

bool connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("mahjoub");//inserer le nom de la source de données ODBC
db.setUserName("mahjoub");//inserer nom de l'utilisateur
db.setPassword("mahjoub");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

