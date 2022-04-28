#include "networkazsdata.h"
#include "LoggingCategories/loggingcategories.h"

#include <QSqlQuery>
#include <QSqlError>

NetworkAzsData::NetworkAzsData(int ID) :
    networkID(ID)
{
    QSqlQuery q;
    q.prepare("select n.network_name, n.logo, n.type_connect, n.HOSTNAME_TYPE_GEN, n.isactive from networkazs n WHERE n.network_id = :netID");
    q.bindValue(":netID", networkID);
    if(!q.exec()){
        qCritical(logCritical()) << "Не могу получить данные о сети АЗС" << q.lastError().text();
    }
    q.next();
    networkName = q.value(0).toString();
    networkLogo = q.value(1).toByteArray();
    typeConnect = q.value(2).toBool();
    hostnameTypeGen = q.value(3).toInt();
    isActive = q.value(4).toBool();
    isChanges = false;
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
    isChanges = true;
}

void NetworkAzsData::setNetworkLogo(const QByteArray &newNetworkLogo)
{
    networkLogo = newNetworkLogo;
    isChanges = true;
}

void NetworkAzsData::setTypeConnect(bool newTypeConnect)
{
    typeConnect = newTypeConnect;
    isChanges = true;
}

void NetworkAzsData::setIsActive(bool newIsActive)
{
    isActive = newIsActive;
    isChanges = true;
}

bool NetworkAzsData::getIsChanges() const
{
    return isChanges;
}

void NetworkAzsData::saveData()
{
    QSqlQuery q;
    q.prepare("UPDATE NETWORKAZS SET NETWORK_NAME = :netName, LOGO = :logo, TYPE_CONNECT = :typeConnect, HOSTNAME_TYPE_GEN = :typeGen, ISACTIVE = :isActive WHERE (NETWORK_ID = :netID)");
    q.bindValue(":netName", networkName);
    q.bindValue(":logo", networkLogo);
    q.bindValue(":typeConnect", typeConnect);
    q.bindValue(":typeGen",hostnameTypeGen);
    q.bindValue(":isActive", isActive);
    q.bindValue(":netID", networkID);
    if(!q.exec()) {
         qCritical(logCritical()) << "Не возможно обновить данные клиента." << q.lastError().text();
    } else {
         qInfo(logInfo()) << "Информация о клиенте обновлена.";
    }
}

int NetworkAzsData::getHostnameTypeGen() const
{
    return hostnameTypeGen;
}

void NetworkAzsData::setHostnameTypeGen(int newHostnameTypeGen)
{
    hostnameTypeGen = newHostnameTypeGen;
    isChanges = true;
}



