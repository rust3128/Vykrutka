QT       += core gui sql

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
    OptionsDialog/CriptPass.cpp \
    OptionsDialog/optionsdialog.cpp \
    Users/users.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DataBase/database.h \
    GlobalSettings/globalsettings.h \
    LoggingCategories/loggingcategories.h \
    OptionsDialog/CriptPass.h \
    OptionsDialog/optionsdialog.h \
    Users/users.h \
    mainwindow.h

FORMS += \
    OptionsDialog/optionsdialog.ui \
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
