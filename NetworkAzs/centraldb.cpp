#include "centraldb.h"
#include "LoggingCategories/loggingcategories.h"

#include <QSqlQuery>
#include <QSqlError>

CentralDB::CentralDB(int ID, QObject *parent)
    : QObject{parent},
      networkID(ID)
{
    readFromDB();
}

void CentralDB::readFromDB()
{
    QSqlQuery q;
    q.prepare("select c.server_name, c.server_port, c.database_file, c.server_user, c.pass from mpos_central_db c where c.network_id = :netID");
    q.bindValue(":netID",networkID);
    if(!q.exec()){
        qCritical(logCritical()) << "Не возможно получить данные о цетральной базе данных." << q.lastError().text();
        initData();
    }
    int numberOfRows = 0;
    if(q.last())
    {
        numberOfRows =  q.at() + 1;
        q.first();
        q.previous();
    }
    if(numberOfRows == 1){
        q.next();
        serverName=q.value(0).toString();
        serverPort = q.value(1).toInt();
        databaseFile = q.value(2).toString();
        serverUser = q.value(3).toString();
        userPass = q.value(4).toString();
        isChanged =false;
    } else {
        initData();
    }
    q.finish();
    q.clear();
}

void CentralDB::initData()
{
    serverName.clear();
    serverPort = 3050;
    databaseFile.clear();
    serverUser.clear();
    userPass.clear();
    isChanged = false;
}

void CentralDB::updateDB()
{
    QSqlQuery q;
    q.prepare("UPDATE OR INSERT INTO MPOS_CENTRAL_DB (NETWORK_ID, SERVER_NAME, SERVER_PORT, DATABASE_FILE, SERVER_USER, PASS) "
              "VALUES (?, ?, ?, ?, ?, ?) "
              "MATCHING (NETWORK_ID)");
    q.bindValue(0,networkID);
    q.bindValue(1,serverName);
    q.bindValue(2,serverPort);
    q.bindValue(3,databaseFile);
    q.bindValue(4,serverUser);
    q.bindValue(5,userPass);

    if(!q.exec()){
        qCritical(logCritical()) << "Не удалось обновить параметры сервера БД" << q.lastError().text();
    } else {
        qInfo(logInfo()) << "Параметры сервера БД успешно обновлены.";
    }
}

void CentralDB::setUserPass(const QString &newUserPass)
{
    userPass = newUserPass;
    isChanged = true;
}

void CentralDB::setServerUser(const QString &newServerUser)
{
    serverUser = newServerUser;
    isChanged = true;
}

void CentralDB::setDatabaseFile(const QString &newDatabaseFile)
{
    databaseFile = newDatabaseFile;
    isChanged = true;
}

void CentralDB::setServerPort(int newServerPort)
{
    serverPort = newServerPort;
    isChanged = true;
}

void CentralDB::setServerName(const QString &newServerName)
{
    serverName = newServerName;
    isChanged = true;
}

bool CentralDB::getIsChanged() const
{
    return isChanged;
}

const QString &CentralDB::getUserPass() const
{
    return userPass;
}

const QString &CentralDB::getServerUser() const
{
    return serverUser;
}

const QString &CentralDB::getDatabaseFile() const
{
    return databaseFile;
}

int CentralDB::getServerPort() const
{
    return serverPort;
}

const QString &CentralDB::getServerName() const
{
    return serverName;
}

int CentralDB::getNetworkID() const
{
    return networkID;
}
