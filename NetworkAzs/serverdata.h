#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <QString>

class ServerData
{
public:
    ServerData();
    unsigned int getServerID() const;
    void setServerID(unsigned int newServerID);

    unsigned int getNetworkID() const;
    void setNetworkID(unsigned int newNetworkID);

    const QString &getServerHost() const;
    void setServerHost(const QString &newServerHost);

    unsigned int getServerPort() const;
    void setServerPort(unsigned int newServerPort);

    const QString &getServerType() const;
    void setServerType(const QString &newServerType);

    bool getIsActive() const;
    void setIsActive(bool newIsActive);

private:
    unsigned int serverID;
    unsigned int networkID;
    QString serverHost;
    unsigned int serverPort;
    QString serverType;
    bool isActive;
};

#endif // SERVERDATA_H
