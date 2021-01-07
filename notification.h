#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QSystemTrayIcon>
#include<QString>


class notification
{
private:
    int num;
public:
    notification();
    void ajoutchantier();
    void ajoutinter();
    void ajoutpark();
    void notification_equi();
    void notification_fourni();
    void notification_employe();
    void notification_poste();

};

#endif // NOTIFICATION_H
