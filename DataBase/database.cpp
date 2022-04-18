#include "database.h"
#include "GlobalSettings/globalsettings.h"
#include "OptionsDialog/optionsdialog.h"
#include "OptionsDialog/CriptPass.h"
#include "LoggingCategories/loggingcategories.h"
#include <QSettings>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

bool DataBase::connectDb()
{
    bool result = false;

    QSettings settings(GlobalSettings::CONFIG_FILE_NAME, QSettings::IniFormat);
    QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE");
    settings.beginGroup("DATABASE");
    db.setHostName(settings.value("Server").toString());
    if(settings.value("Port").toInt()>0){
        db.setPort(settings.value("Port").toInt());
    }
    db.setDatabaseName(settings.value("DataBase").toString());
    db.setUserName(settings.value("User").toString());
    db.setPassword(decriptPass(settings.value("Password").toString()));
    settings.endGroup();

    if(!db.open()) {
        qCritical(logCritical()) <<  "Не возможно подключиться к базе данных." << Qt::endl << "Причина:" << db.lastError().text();

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка подключения к базе данных!");
        msgBox.setInformativeText("Проверить настройки подключения?");
        msgBox.setStandardButtons(QMessageBox::Yes |  QMessageBox::No);
        msgBox.setDetailedText(db.lastError().text());
        int ret = msgBox.exec();

        if(ret == QMessageBox::Yes) {
            OptionsDialog *optDlg = new OptionsDialog(false);
            int result = optDlg->exec();
            if(result == QDialog::Accepted) {
                qInfo(logInfo()) << "Сохранение настроек подключения.";
            }
        }
        //Завершаем работу
        result = false;
    } else {
        qInfo(logInfo()) << "Успешное подключение к центральной базе данных.";
        result = true;
    }
    return result;
}
