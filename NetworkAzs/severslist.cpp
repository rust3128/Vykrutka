#include "severslist.h"
#include "LoggingCategories/loggingcategories.h"

#include <QSqlQuery>
#include <QSqlError>

SeversList::SeversList(uint netID, QObject *parent)
    : QObject{parent},
      networkID(netID)
{
    createListServeres();
}

const QList<ServerData> &SeversList::getListServ() const
{
    return listServ;
}

void SeversList::createListServeres()
{
    listServ.clear();
    QSqlQuery q;
    q.prepare("select s.server_id, s.server_host, s.server_port, s.server_type, s.isactive from servers s where s.network_id = :netID");
    q.bindValue(":netID",networkID);
    if(!q.exec()){
        qCritical(logCritical()) << "Не удалось получить список серверов" << q.lastError().text();
    } else {
        while (q.next()) {
            servData.setServerID(q.value(0).toUInt());
            servData.setNetworkID(networkID);
            servData.setServerHost(q.value(1).toString());
            servData.setServerPort(q.value(2).toUInt());
            servData.setServerType(q.value(3).toString());
            servData.setIsActive(q.value(4).toBool());
            listServ.append(servData);
        }
    }
}
