#include "serverdata.h"

ServerData::ServerData()
{

}

unsigned int ServerData::getServerID() const
{
    return serverID;
}

void ServerData::setServerID(unsigned int newServerID)
{
    serverID = newServerID;
}

unsigned int ServerData::getNetworkID() const
{
    return networkID;
}

void ServerData::setNetworkID(unsigned int newNetworkID)
{
    networkID = newNetworkID;
}

const QString &ServerData::getServerHost() const
{
    return serverHost;
}

void ServerData::setServerHost(const QString &newServerHost)
{
    serverHost = newServerHost;
}

unsigned int ServerData::getServerPort() const
{
    return serverPort;
}

void ServerData::setServerPort(unsigned int newServerPort)
{
    serverPort = newServerPort;
}

const QString &ServerData::getServerType() const
{
    return serverType;
}

void ServerData::setServerType(const QString &newServerType)
{
    serverType = newServerType;
}

bool ServerData::getIsActive() const
{
    return isActive;
}

void ServerData::setIsActive(bool newIsActive)
{
    isActive = newIsActive;
}
