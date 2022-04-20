#ifndef USERS_H
#define USERS_H

#include <QObject>

class Users
{
//    Q_OBJECT
public:
    Users(QString systemuser);
    int getUserID() const;

    const QString &getUserLogin() const;

    const QString &getUserFIO() const;

    const QString &getAsterPhone() const;

    const QString &getMobilePhone() const;

    int getLangUI() const;

    bool getIsActive() const;

private:
    void getUserData();
private:
    int userID;
    QString userLogin;
    QString userFIO;
    QString asterPhone;
    QString mobilePhone;
    int langUI;
    bool isActive;
};

#endif // USERS_H
