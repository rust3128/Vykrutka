#ifndef NETWORKAZSDATA_H
#define NETWORKAZSDATA_H

#include <QString>

class NetworkAzsData
{
public:
    NetworkAzsData(int ID);
    int getNetworkID() const;

    const QString &getNetworkName() const;

    const QByteArray &getNetworkLogo() const;

    bool getTypeConnect() const;

    bool getIsActive() const;

    void setNetworkName(const QString &newNetworkName);

    void setNetworkLogo(const QByteArray &newNetworkLogo);

    void setTypeConnect(bool newTypeConnect);

    void setIsActive(bool newIsActive);

private:
    int networkID;
    QString networkName;
    QByteArray networkLogo;
    bool typeConnect;
    bool isActive;
};

#endif // NETWORKAZSDATA_H
