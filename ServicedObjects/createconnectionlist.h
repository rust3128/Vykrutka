#ifndef CREATECONNECTIONLIST_H
#define CREATECONNECTIONLIST_H

#include "NetworkAzs/templatehostname.h"
#include "NetworkAzs/centraldb.h"

#include <QObject>

class CreateConnectionList : public QObject
{
    Q_OBJECT
public:
    explicit CreateConnectionList(uint netID, uint termID, QObject *parent = nullptr);

    const QList<QStringList> &getConnList() const;

signals:
private:
    void createConnectionList();
    void getOwnerID();
    void getPassVNC();
private:
    uint terminalID;
    uint networkID;
    QString hostName;
    uint port;
    QString passVNC;
    QList<QStringList> connList;
    TemplateHostname *templHost;
    uint codeCh;
    uint ownerID;
    CentralDB *centralDB;
};

#endif // CREATECONNECTIONLIST_H
