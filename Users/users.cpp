#include "users.h"
#include "LoggingCategories/loggingcategories.h"

#include <QSqlQuery>
#include <QSqlError>

Users::Users(QString systemuser) :
    userLogin(systemuser)
{

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

}
