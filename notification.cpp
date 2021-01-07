#include "notification.h"

notification::notification()
{

}


void notification::ajoutchantier()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("News","Un chantier à été ajouter  !",QSystemTrayIcon::Information,15000);

}
void notification::ajoutinter()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("News","Un intervenat à été ajouter  !",QSystemTrayIcon::Information,15000);

}
void notification::ajoutpark()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("News","Un parking à été ajouter  !",QSystemTrayIcon::Information,15000);

}
void notification::notification_equi()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("News","Un equipement à été ajouter  !",QSystemTrayIcon::Information,15000);

}
void notification::notification_fourni()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("News","Un fournisseur à été ajouter  !",QSystemTrayIcon::Information,15000);

}
void notification::notification_poste()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("News","Une poste à été ajouter  !",QSystemTrayIcon::Information,15000);

}
void notification::notification_employe()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("News","Un employé à été ajouter  !",QSystemTrayIcon::Information,15000);

}
