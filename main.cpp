#include "mainwindow.h"
#include "LoggingCategories/loggingcategories.h"
#include "GlobalSettings/globalsettings.h"
#include "OptionsDialog/optionsdialog.h"
#include "DataBase/database.h"
#include "Users/users.h"
#include "Users/userdatadialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

// Умный указатель на файл логирования
static QScopedPointer<QFile>   m_logFile;

// Объявление обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем файл логирования
    m_logFile.reset(new QFile(GlobalSettings::LOG_FILE));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);


    // Загрузка файла настроек
    QFile configFile;
    configFile.setFileName(GlobalSettings::CONFIG_FILE_NAME);
    if(!configFile.exists()) {
        qCritical(logCritical()) << "Не найден конфигурационный файл!";
        auto result = QMessageBox::question(nullptr,"Ошибка","Не найден файл настроек!\nВыполнить настройку приложения?");
        if(result == QMessageBox::Yes){
            OptionsDialog *optDlg = new OptionsDialog(true);
            optDlg->exec();
        }
        return 1;
    }

    DataBase *db = new DataBase();
        if(!db->connectDb()){
            qCritical(logCritical()) << "Аварийное завершение работы.";
            return 1;
        }

    //Опредкляем пользователя
    QString qUsername;
#if defined(Q_OS_WIN)
    qUsername=QString::fromLocal8Bit (qgetenv ("USERNAME").constData ()).toUtf8 ();
#elif defined(Q_OS_UNIX)
    qUsername=qgetenv("USER").constData ();
#endif

    QSqlQuery q;
    q.prepare("EXECUTE PROCEDURE get_user_id(:username)");
    q.bindValue(":username", qUsername);
    if(!q.exec()){
        qCritical(logCritical()) << q.lastError().text();
        return 1;
    }
    q.next();
    bool isNew = q.value(1).toBool();
    int userID = q.value(0).toInt();
    q.exec("commit work");

    if(isNew){
        //Новый пользователь
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, QApplication::tr("Новый пользователь"),
                                        QApplication::tr("Вы первый раз запустили программу. Необходимо заполнить ваши данные.\nСогласны?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            //Диалог редактирования пользователя
            UserDataDialog *usData = new UserDataDialog(userID);
            usData->exec();
        }
    }

    Users *curUser = new Users(userID);
    //Загрузка локализации
    int lang = curUser->getLangUI();
    qInfo(logInfo()) << "LangID" << lang;
    QTranslator *trans = new QTranslator();
    QTranslator *guiTrans = new QTranslator();
    switch (lang) {
    case 1:
        if(trans->load(":/Vykrutka_RU_ua.qm"))
            a.installTranslator(trans);
        if(guiTrans->load(":/Translations/qtbase_uk.qm"))
            a.installTranslator(guiTrans);
        break;
    case 2:
        if(trans->load(":/Vykrutka_RU_en.qm"))
            a.installTranslator(trans);
        if(guiTrans->load(":/Translations/qtbase_en.qm"))
            a.installTranslator(guiTrans);
        break;
    default:
        if(guiTrans->load(":/Translations/qtbase_ru.qm"))
            a.installTranslator(guiTrans);
        break;
    }

    q.finish();
    MainWindow w = MainWindow(curUser);
    w.show();
    qInfo(logInfo()) << "Started...";
    return a.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    QTextStream console(stdout);
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
#ifdef QT_DEBUG
    case QtInfoMsg:
        out << "[INF] ";
        console << "Info:     " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << Qt::endl;
        break;
    case QtDebugMsg:
        out << "[DBG] " ;
        console << "Debug:    " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << Qt::endl;
        break;
    case QtWarningMsg:
        out << "[WRN] ";
        console << "Warning:  " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] "  << Qt::endl;
        break;
    case QtCriticalMsg:
        out << "[CRT] ";
        console << "Critical: " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << Qt::endl;
        break;
    case QtFatalMsg:
        out << "[FTL] ";
        console << "Fatality: " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << Qt::endl;
        break;
#else
    case QtInfoMsg:     out << "[INF] "; break;
    case QtDebugMsg:    out << "[DBG] "; break;
    case QtWarningMsg:  out << "[WRN] "; break;
    case QtCriticalMsg: out << "[CRT] "; break;
    case QtFatalMsg:    out << "[FTL] "; break;
#endif

    }

    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": " << msg;
    out << "  ***[" << context.function << " File: " << context.file << " Line: " << context.line << "]***" << Qt::endl;
    // Очищаем буферизированные данные
    out.flush();
    console.flush();
}
