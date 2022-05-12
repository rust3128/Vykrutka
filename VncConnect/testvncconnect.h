#ifndef TESTVNCCONNECT_H
#define TESTVNCCONNECT_H
#include "ServicedObjects/statuspos.h"
#include <QObject>
#include <QHash>

class TestVNCConnect : public QObject
{
    Q_OBJECT
public:
    explicit TestVNCConnect(QString _host, uint _port, uint _pID, QObject *parent = nullptr);

signals:
    void signalSendStatusConnect(StatusPos);
    void finish();
    void statusConnChanged();

public slots:
    void checkConnectionStatus();
private:
    QString hostName;
    uint port;
    uint posID;
    StatusPos statusConn;
};

#endif // TESTVNCCONNECT_H
