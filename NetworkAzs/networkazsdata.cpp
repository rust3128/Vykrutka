#include "networkazsdata.h"
#include "LoggingCategories/loggingcategories.h"

#include <QSqlQuery>
#include <QSqlError>

NetworkAzsData::NetworkAzsData(int ID) :
    networkID(ID)
{
    QSqlQuery q;
    q.prepare("select n.network_name, n.logo, n.type_connect, n.isactive from networkazs n WHERE n.network_id = :netID");
    q.bindValue(":netID", networkID);
    if(!q.exec()){
        qCritical(logCritical()) << "Не могу получить данные о сети АЗС" << q.lastError().text();
    }
    q.next();
    networkName = q.value(0).toString();
    networkLogo = q.value(1).toByteArray();
    typeConnect = q.value(2).toBool();
    isActive = q.value(3).toBool();
}

int NetworkAzsData::getNetworkID() const
{
    return networkID;
}

const QString &NetworkAzsData::getNetworkName() const
{
    return networkName;
}

const QByteArray &NetworkAzsData::getNetworkLogo() const
{
    return networkLogo;
}

bool NetworkAzsData::getTypeConnect() const
{
    return typeConnect;
}

bool NetworkAzsData::getIsActive() const
{
    return isActive;
}

void NetworkAzsData::setNetworkName(const QString &newNetworkName)
{
    networkName = newNetworkName;
}

void NetworkAzsData::setNetworkLogo(const QByteArray &newNetworkLogo)
{
    networkLogo = newNetworkLogo;
}

void NetworkAzsData::setTypeConnect(bool newTypeConnect)
{
    typeConnect = newTypeConnect;
}

void NetworkAzsData::setIsActive(bool newIsActive)
{
    isActive = newIsActive;
}
