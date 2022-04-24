#ifndef USERS_H
#define USERS_H

#include <QObject>

class Users : public QObject
{
    Q_OBJECT
public:
    Users(int ID, QObject *parent = nullptr);
    int getUserID() const;

    const QString &getUserLogin() const;

    const QString &getUserFIO() const;

    const QString &getAsterPhone() const;

    const QString &getMobilePhone() const;

    int getLangUI() const;

    bool getIsActive() const;

    const QString &getEmail() const;

    const QString &getLangName() const;

private:
    void getUserData();
private:
    int userID;
    QString userLogin;
    QString userFIO;
    QString asterPhone;
    QString mobilePhone;
    QString email;
    int langUI;
    bool isActive;
    QString langName;
};

#endif // USERS_H
