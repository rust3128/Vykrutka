#include "testvncconnect.h"
#include "LoggingCategories/loggingcategories.h"


#include <QTcpSocket>

TestVNCConnect::TestVNCConnect(QString _host, uint _port,uint _pID, QObject *parent)
    : QObject{parent},
      hostName(_host),
      port(_port)
{
    statusConn.setPosID(_pID);
}

void TestVNCConnect::checkConnectionStatus()
{
    QTcpSocket *tcpSocket = new QTcpSocket();

    tcpSocket->connectToHost(hostName,port);
    if(tcpSocket->waitForConnected(2000)){
        statusConn.setConnected(true);
    } else {
        statusConn.setConnected(false);
    }
    emit signalSendStatusConnect(statusConn);
    emit finish();
}

