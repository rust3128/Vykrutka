#include "users.h"
#include "LoggingCategories/loggingcategories.h"

#include <QSqlQuery>
#include <QSqlError>

Users::Users(int ID, QObject *parent) : QObject(parent),
    userID(ID)
{
    getUserData();
}

int Users::getUserID() const
{
    return userID;
}

const QString &Users::getUserLogin() const
{
    return userLogin;
}

const QString &Users::getUserFIO() const
{
    return userFIO;
}

const QString &Users::getAsterPhone() const
{
    return asterPhone;
}

const QString &Users::getMobilePhone() const
{
    return mobilePhone;
}

int Users::getLangUI() const
{
    return langUI;
}

bool Users::getIsActive() const
{
    return isActive;
}

void Users::getUserData()
{
    QSqlQuery q;
    q.prepare("select u.user_login, u.user_fio, u.aster_phone, u.phone, u.email, u.uilang, u.isactibe from users u "
              "where u.user_id =:uID");
    q.bindValue(":uID", userID);
    if(!q.exec()){
        qCritical(logCritical()) << "Unable to complete request" << q.lastError().text();
        return;
    }
    q.next();
    userLogin = q.value(0).toString();
    userFIO = q.value(1).toString();
    asterPhone = q.value(2).toString();
    mobilePhone = q.value(3).toString();
    email = q.value(4).toString();
    langUI = q.value(5).toInt();
    isActive = q.value(6).toBool();
    q.finish();

}

const QString &Users::getEmail() const
{
    return email;
}
