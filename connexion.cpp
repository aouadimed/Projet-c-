#include "connexion.h"
#include <QString>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_2A11");//inserer le nom de la source de données ODBC
db.setUserName("mohamed");//inserer nom de l'utilisateur
db.setPassword("aouadi");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

else
     {test=false;}

    return  test;
}
void Connection::fermerConnection()
{
    db.close();
}


