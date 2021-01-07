#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include <QCoreApplication>
#include <QtSql>
#include <QDebug>
#include "authentification.h"
#include "ui_mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    MainWindow w;
    w.setWindowTitle("Smart Municipality");
    w.setFixedSize(991,702);
    w.setWindowIcon(QIcon(":/images/18533.png"));
    bool test=c.createconnect();
    if(test)
    {w.show();
        w.ui->stackedWidget->setCurrentIndex(0);


        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
