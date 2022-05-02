#include "templatehostname.h"
#include "LoggingCategories/loggingcategories.h"

#include <QSqlQuery>
#include <QSqlError>

TemplateHostname::TemplateHostname(uint ID, QObject *parent)
    : QObject{parent},
      networkID(ID)
{
    readFromDB();
}

void TemplateHostname::readFromDB()
{
    QSqlQuery q;
    q.prepare("SELECT t.max_posid, t.single_vnc_port, t.vnc_port, t.prefix, t.prefix_chage, t.use_terminal_id, t.sufics_change, t.sufix from template_vnc t where t.network_id = :ID");
    q.bindValue(":ID",networkID);
    if(!q.exec()){
        qCritical(logCritical()) << "Не возможно получить данные для шаблона" << q.lastError().text();
        initData();
        return;
    }
    int numberOfRows = 0;
    if(q.last())
    {
        numberOfRows =  q.at() + 1;
        q.first();
        q.previous();
    }
    if(numberOfRows == 1){
        q.next();
        maxPOSID = q.value(0).toUInt();
        singleVNCPort = q.value(1).toBool();
        VNCPort = q.value(2).toUInt();
        prefix = q.value(3).toString();
        prefixChange = q.value(4).toChar();
        useTermID = q.value(5).toBool();
        sufixChange = q.value(6).toChar();
        sufix = q.value(7).toString();
        isChange = false;
    } else {
        initData();
    }
    q.finish();
    q.clear();
}

void TemplateHostname::initData()
{
    maxPOSID =4;
    singleVNCPort = true;
    VNCPort = 5900;
    prefix.clear();
    prefixChange = QChar();
    useTermID = true;
    sufixChange = QChar();
    sufix.clear();
    isChange =false;
}

void TemplateHostname::saveToDB()
{
    QSqlQuery q;
    q.prepare("UPDATE OR INSERT INTO TEMPLATE_VNC (NETWORK_ID, MAX_POSID, SINGLE_VNC_PORT, VNC_PORT, PREFIX, PREFIX_CHAGE, USE_TERMINAL_ID, SUFICS_CHANGE, SUFIX) "
              "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?) "
              "MATCHING (NETWORK_ID)");
    q.bindValue(0, networkID);
    q.bindValue(1, maxPOSID);
    q.bindValue(2, singleVNCPort);
    q.bindValue(3, VNCPort);
    q.bindValue(4, prefix);
    q.bindValue(5, prefixChange);
    q.bindValue(6, useTermID);
    q.bindValue(7, sufixChange);
    q.bindValue(8, sufix);
    if(!q.exec()){
        qCritical(logCritical()) << "Не удалось обновить параметры шаблона подключения" << q.lastError().text();
    } else {
        qInfo(logInfo()) << "Параметры параметры шаблона подключения успешно обновлены.";
    }
}

uint TemplateHostname::getNetworkID() const
{
    return networkID;
}

void TemplateHostname::setNetworkID(uint newNetworkID)
{
    networkID = newNetworkID;
    isChange = true;
}

uint TemplateHostname::getMaxPOSID() const
{
    return maxPOSID;
}

void TemplateHostname::setMaxPOSID(uint newMaxPOSID)
{
    maxPOSID = newMaxPOSID;
    isChange = true;
}

bool TemplateHostname::getSingleVNCPort() const
{
    return singleVNCPort;
}

void TemplateHostname::setSingleVNCPort(bool newSingleVNCPort)
{
    singleVNCPort = newSingleVNCPort;
    isChange = true;
}

uint TemplateHostname::getVNCPort() const
{
    return VNCPort;
}

void TemplateHostname::setVNCPort(uint newVNCPort)
{
    VNCPort = newVNCPort;
    isChange = true;
}

const QString &TemplateHostname::getPrefix() const
{
    return prefix;
}

void TemplateHostname::setPrefix(const QString &newPrefix)
{
    prefix = newPrefix;
    isChange = true;
}

const QChar &TemplateHostname::getPrefixChange() const
{
    return prefixChange;
}

void TemplateHostname::setPrefixChange(const QChar &newPrefixChange)
{
    prefixChange = newPrefixChange;
    isChange = true;
}

bool TemplateHostname::getUseTermID() const
{
    return useTermID;
}

void TemplateHostname::setUseTermID(bool newUseTermID)
{
    useTermID = newUseTermID;
    isChange = true;
}

const QChar &TemplateHostname::getSufixChange() const
{
    return sufixChange;
}

void TemplateHostname::setSufixChange(const QChar &newSufixChange)
{
    sufixChange = newSufixChange;
    isChange = true;
}

const QString &TemplateHostname::getSufix() const
{
    return sufix;
}

void TemplateHostname::setSufix(const QString &newSufix)
{
    sufix = newSufix;
    isChange = true;
}

bool TemplateHostname::getIsChange() const
{
    return isChange;
}

void TemplateHostname::setIsChange(bool newIsChange)
{
    isChange = newIsChange;
}


