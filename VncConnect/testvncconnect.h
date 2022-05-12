#ifndef TESTVNCCONNECT_H
#define TESTVNCCONNECT_H

#include <QObject>

class TestVNCConnect : public QObject
{
    Q_OBJECT
public:
    explicit TestVNCConnect(QString _host, uint _port, QObject *parent = nullptr);

signals:
    void signalSendStatusConnect(bool);
    void finish();
public slots:
    void checkConnectionStatus();
private:
    QString hostName;
    uint port;
    bool statusConn;
};

#endif // TESTVNCCONNECT_H
