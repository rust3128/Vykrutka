#ifndef USERDATADIALOG_H
#define USERDATADIALOG_H

#include "Users/users.h"
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class UserDataDialog;
}

class UserDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDataDialog(int ID, QWidget *parent = nullptr);
    ~UserDataDialog();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    void createUI();
private:
    Ui::UserDataDialog *ui;
    int userID;
    Users *currentUser;
    QSqlQueryModel *modelLang;
};

#endif // USERDATADIALOG_H
