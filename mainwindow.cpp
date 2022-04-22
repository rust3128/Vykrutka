#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LoggingCategories/loggingcategories.h"
#include "Users/userdatadialog.h"

#include <QMessageBox>

MainWindow::MainWindow(Users *u, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _currentUser(u)
{
    ui->setupUi(this);

    createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUI()
{
    //Настройка и создание интерфейса
}




void MainWindow::on_actionUser_triggered()
{
    //Данные пользователя
    UserDataDialog *userDlg = new UserDataDialog(_currentUser->getUserID(),this);
    userDlg->exec();
}

