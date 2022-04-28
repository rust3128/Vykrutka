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
    bool getIsChanges() const;

    void saveData();

    int getHostnameTypeGen() const;
    void setHostnameTypeGen(int newHostnameTypeGen);

private:
    int networkID;
    QString networkName;
    QByteArray networkLogo;
    bool typeConnect;
    int hostnameTypeGen;
    bool isActive;
    bool isChanges;
};

#endif // NETWORKAZSDATA_H
