#ifndef CENTRALDB_H
#define CENTRALDB_H

#include <QObject>
#include <QSqlDatabase>

class CentralDB : public QObject
{
    Q_OBJECT
public:
    explicit CentralDB(int ID, QObject *parent = nullptr);
    int getNetworkID() const;
    const QString &getServerName() const;
    int getServerPort() const;
    const QString &getDatabaseFile() const;
    const QString &getServerUser() const;
    const QString &getUserPass() const;
    bool getIsChanged() const;
    void setServerName(const QString &newServerName);
    void setServerPort(int newServerPort);
    void setDatabaseFile(const QString &newDatabaseFile);
    void setServerUser(const QString &newServerUser);
    void setUserPass(const QString &newUserPass);
    void updateDB();
    const QSqlDatabase &getDbCentr() const;
    void createCentrDB();
signals:

private:
    void readFromDB();
    void initData();

private:
    int networkID;
    QString serverName;
    int serverPort;
    QString databaseFile;
    QString serverUser;
    QString userPass;
    bool isChanged;
    QSqlDatabase dbCenter;


};

#endif // CENTRALDB_H
