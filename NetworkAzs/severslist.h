#ifndef SEVERSLIST_H
#define SEVERSLIST_H
#include "NetworkAzs/serverdata.h"

#include <QObject>


class SeversList : public QObject
{
    Q_OBJECT
public:
    explicit SeversList(uint netID, QObject *parent = nullptr);

    const QList<ServerData> &getListServ() const;

signals:
private:
    void createListServeres();
private:
    QList<ServerData> listServ;
    ServerData servData;
    uint networkID;
};

#endif // SEVERSLIST_H
