#include "createconnectionlist.h"
#include "LoggingCategories/loggingcategories.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

CreateConnectionList::CreateConnectionList(uint netID, uint termID, QObject *parent)
    : QObject{parent},
      terminalID(termID),
      networkID(netID)
{
    createConnectionList();
}

const QList<QStringList> &CreateConnectionList::getConnList() const
{
    return connList;
}

void CreateConnectionList::createConnectionList()
{
    templHost = new TemplateHostname(networkID, this);
    QStringList paramVNC;
    getOwnerID();

    for(uint i=0; i<templHost->getMaxPOSID();++i){
        hostName.clear();
        paramVNC.clear();
        if(templHost->getPrefix().size()>0){
            hostName += templHost->getPrefix();
        }
        if(!templHost->getPrefixChange().isNull()){
            codeCh = templHost->getPrefixChange().toLatin1();
            hostName += QChar(codeCh+i);
        }
        if(templHost->getUseTermID()){
            hostName += QString::number(terminalID);
        } else {
            hostName += QString::number(ownerID);
        }
        if(!templHost->getSufixChange().isNull()){
            codeCh = templHost->getSufixChange().toLatin1();
            hostName += QChar(codeCh+i);
        }
        if(templHost->getSufix().size()>0){
            hostName += templHost->getSufix();
        }
        if(templHost->getSingleVNCPort()){
            port = templHost->getVNCPort();
        } else {
            port = templHost->getVNCPort() + i;
        }
        getPassVNC();
        paramVNC << hostName << QString::number(port) << passVNC;
        connList.append(paramVNC);
    }
}

void CreateConnectionList::getOwnerID()
{
    centralDB = new CentralDB(networkID,this);
    centralDB->createCentrDB();
    QSqlDatabase d = QSqlDatabase::database("centr");
    if(d.open()){
        QSqlQuery q(d);
        q.prepare("select t.ownersystem_id from terminals t where t.terminal_id = :tID");
        q.bindValue(":tID",terminalID);
        if(!q.exec()) {
            qCritical(logCritical()) << "Не могу получить OWNERSYSTEM_ID из базы данных!" << q.lastError().text();
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("Ошибка получения данных"));
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText(tr("Не могу получить OWNERSYSTEM_ID из базы данных!"));
            msgBox.setDetailedText(q.lastError().text());
            msgBox.exec();
            ownerID=0;
        } else {
            q.next();
            ownerID = q.value(0).toUInt();
        }

    } else {
        qCritical (logCritical()) << "Ошибка подключения к ЦБ" << d.lastError().text();
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Ошибка подключения"));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(tr("Ошибка подключения к центральной базе данных!"));
        msgBox.setDetailedText(d.lastError().text());
        msgBox.exec();
        ownerID = 0;
    }

}

void CreateConnectionList::getPassVNC()
{
    passVNC = "88888888";
}
