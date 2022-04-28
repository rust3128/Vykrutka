#include "templatehostname.h"

TemplateHostname::TemplateHostname(uint ID, QObject *parent)
    : QObject{parent},
      networkID(ID)
{

}

uint TemplateHostname::getNetworkID() const
{
    return networkID;
}

void TemplateHostname::setNetworkID(uint newNetworkID)
{
    networkID = newNetworkID;
}

uint TemplateHostname::getMaxPOSID() const
{
    return maxPOSID;
}

void TemplateHostname::setMaxPOSID(uint newMaxPOSID)
{
    maxPOSID = newMaxPOSID;
}

bool TemplateHostname::getSingleVNCPort() const
{
    return singleVNCPort;
}

void TemplateHostname::setSingleVNCPort(bool newSingleVNCPort)
{
    singleVNCPort = newSingleVNCPort;
}

uint TemplateHostname::getVNCPort() const
{
    return VNCPort;
}

void TemplateHostname::setVNCPort(uint newVNCPort)
{
    VNCPort = newVNCPort;
}

const QString &TemplateHostname::getPrefix() const
{
    return prefix;
}

void TemplateHostname::setPrefix(const QString &newPrefix)
{
    prefix = newPrefix;
}

const QChar &TemplateHostname::getPrefixChange() const
{
    return prefixChange;
}

void TemplateHostname::setPrefixChange(const QChar &newPrefixChange)
{
    prefixChange = newPrefixChange;
}

bool TemplateHostname::getUseTermID() const
{
    return useTermID;
}

void TemplateHostname::setUseTermID(bool newUseTermID)
{
    useTermID = newUseTermID;
}

const QChar &TemplateHostname::getSufixChange() const
{
    return sufixChange;
}

void TemplateHostname::setSufixChange(const QChar &newSufixChange)
{
    sufixChange = newSufixChange;
}

const QString &TemplateHostname::getSufix() const
{
    return sufix;
}

void TemplateHostname::setSufix(const QString &newSufix)
{
    sufix = newSufix;
}

bool TemplateHostname::getIsChange() const
{
    return isChange;
}

void TemplateHostname::setIsChange(bool newIsChange)
{
    isChange = newIsChange;
}
