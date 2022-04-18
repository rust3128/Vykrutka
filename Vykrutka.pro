QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32: RC_ICONS = $$PWD/Images/Vykrutka.ico


SOURCES += \
    GlobalSettings/globalsettings.cpp \
    LoggingCategories/loggingcategories.cpp \
    OptionsDialog/CriptPass.cpp \
    OptionsDialog/optionsdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GlobalSettings/globalsettings.h \
    LoggingCategories/loggingcategories.h \
    OptionsDialog/CriptPass.h \
    OptionsDialog/optionsdialog.h \
    mainwindow.h

FORMS += \
    OptionsDialog/optionsdialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    Vykrutka_uk_UA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
