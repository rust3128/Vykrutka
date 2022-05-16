QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32: RC_ICONS = $$PWD/Images/Vykrutka.ico


SOURCES += \
    DataBase/database.cpp \
    GlobalSettings/globalsettings.cpp \
    LoggingCategories/loggingcategories.cpp \
    NetworkAzs/centraldb.cpp \
    NetworkAzs/editnetworkazsdialog.cpp \
    NetworkAzs/logodelegate.cpp \
    NetworkAzs/modelnetworkazs.cpp \
    NetworkAzs/networkazsdata.cpp \
    NetworkAzs/networkazsdialog.cpp \
    NetworkAzs/serverdata.cpp \
    NetworkAzs/severslist.cpp \
    NetworkAzs/templatehostname.cpp \
    NetworkAzs/testtemplatedialog.cpp \
    NetworkAzs/vncbutton.cpp \
    OptionsDialog/CriptPass.cpp \
    OptionsDialog/optionsdialog.cpp \
    ServicedObjects/createconnectionlist.cpp \
    ServicedObjects/poslistwidget.cpp \
    ServicedObjects/statuspos.cpp \
    Users/userdatadialog.cpp \
    Users/users.cpp \
    VncConnect/testvncconnect.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DataBase/database.h \
    GlobalSettings/globalsettings.h \
    LoggingCategories/loggingcategories.h \
    NetworkAzs/centraldb.h \
    NetworkAzs/editnetworkazsdialog.h \
    NetworkAzs/logodelegate.h \
    NetworkAzs/modelnetworkazs.h \
    NetworkAzs/networkazsdata.h \
    NetworkAzs/networkazsdialog.h \
    NetworkAzs/serverdata.h \
    NetworkAzs/severslist.h \
    NetworkAzs/templatehostname.h \
    NetworkAzs/testtemplatedialog.h \
    NetworkAzs/vncbutton.h \
    OptionsDialog/CriptPass.h \
    OptionsDialog/optionsdialog.h \
    ServicedObjects/createconnectionlist.h \
    ServicedObjects/poslistwidget.h \
    ServicedObjects/statuspos.h \
    Users/userdatadialog.h \
    Users/users.h \
    VncConnect/testvncconnect.h \
    mainwindow.h

FORMS += \
    NetworkAzs/editnetworkazsdialog.ui \
    NetworkAzs/networkazsdialog.ui \
    NetworkAzs/testtemplatedialog.ui \
    OptionsDialog/optionsdialog.ui \
    ServicedObjects/poslistwidget.ui \
    Users/userdatadialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    Vykrutka_RU_en.ts
TRANSLATIONS += \
    Vykrutka_RU_ua.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    Translations/Vykrutka_RU_en.ts \
    Translations/Vykrutka_RU_ua.ts
