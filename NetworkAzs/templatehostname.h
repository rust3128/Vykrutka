#ifndef TEMPLATEHOSTNAME_H
#define TEMPLATEHOSTNAME_H

#include <QObject>

class TemplateHostname : public QObject
{
    Q_OBJECT
public:
    explicit TemplateHostname(uint ID, QObject *parent = nullptr);

    uint getNetworkID() const;
    void setNetworkID(uint newNetworkID);

    uint getMaxPOSID() const;
    void setMaxPOSID(uint newMaxPOSID);

    bool getSingleVNCPort() const;
    void setSingleVNCPort(bool newSingleVNCPort);

    uint getVNCPort() const;
    void setVNCPort(uint newVNCPort);

    const QString &getPrefix() const;
    void setPrefix(const QString &newPrefix);

    const QChar &getPrefixChange() const;
    void setPrefixChange(const QChar &newPrefixChange);

    bool getUseTermID() const;
    void setUseTermID(bool newUseTermID);

    const QChar &getSufixChange() const;
    void setSufixChange(const QChar &newSufixChange);

    const QString &getSufix() const;
    void setSufix(const QString &newSufix);

    bool getIsChange() const;
    void setIsChange(bool newIsChange);

signals:

private:
    void readFromDB();
    void initData();
private:
    uint networkID;
    uint maxPOSID;
    bool singleVNCPort;
    uint VNCPort;
    QString prefix;
    QChar prefixChange;
    bool useTermID;
    QChar sufixChange;
    QString sufix;
    bool isChange;
};

#endif // TEMPLATEHOSTNAME_H
