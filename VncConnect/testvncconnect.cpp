#include "testvncconnect.h"
#include "LoggingCategories/loggingcategories.h"


#include <QTcpSocket>

TestVNCConnect::TestVNCConnect(QString _host, uint _port, QObject *parent)
    : QObject{parent},
      hostName(_host),
      port(_port)
{

}

void TestVNCConnect::checkConnectionStatus()
{
    QTcpSocket *tcpSocket = new QTcpSocket();

    tcpSocket->connectToHost(hostName,port);
    if(tcpSocket->waitForConnected(2000)){
        statusConn = true;
    } else {
        statusConn = false;
    }
    emit signalSendStatusConnect(statusConn);
    emit finish();
}
