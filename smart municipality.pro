QT       += core gui sql printsupport charts serialport
QT       +=multimedia
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    chantier.cpp \
    connexion.cpp \
    employe.cpp \
    equipements.cpp \
    fournisseur.cpp \
    intervenant.cpp \
    mailing/emailaddress.cpp \
    mailing/mimeattachment.cpp \
    mailing/mimecontentformatter.cpp \
    mailing/mimefile.cpp \
    mailing/mimehtml.cpp \
    mailing/mimeinlinefile.cpp \
    mailing/mimemessage.cpp \
    mailing/mimemultipart.cpp \
    mailing/mimepart.cpp \
    mailing/mimetext.cpp \
    mailing/quotedprintable.cpp \
    mailing/smtpclient.cpp \
    main.cpp \
    mainwindow.cpp \
    notification.cpp \
    parking.cpp \
    poste.cpp \
    stat.cpp

HEADERS += \
    arduino.h \
    chantier.h \
    connexion.h \
    employe.h \
    equipements.h \
    fournisseur.h \
    intervenant.h \
    mailing/SmtpMime \
    mailing/emailaddress.h \
    mailing/mimeattachment.h \
    mailing/mimecontentformatter.h \
    mailing/mimefile.h \
    mailing/mimehtml.h \
    mailing/mimeinlinefile.h \
    mailing/mimemessage.h \
    mailing/mimemultipart.h \
    mailing/mimepart.h \
    mailing/mimetext.h \
    mailing/quotedprintable.h \
    mailing/smtpclient.h \
    mailing/smtpexports.h \
    mainwindow.h \
    notification.h \
    parking.h \
    poste.h \
    stat.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    images/62263273-concept-de-l-ingénierie-des-outils-de-construction-sur-une-illustration-blanche-background-3d.jpg \
    images/Achat-fourniture-bureau.jpg \
    images/La-transformation-digitale-de-la-relation-client-fournisseur-01-1030x399.jpg \
    images/Sans titre-1.jpg \
    images/co.PNG \
    images/construisez-une-relation-fournisseur-solide.jpg \
    images/find_files_on_linux.jpg \
    images/istockphoto-507065413-170667a.jpg
