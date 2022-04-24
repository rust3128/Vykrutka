#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LoggingCategories/loggingcategories.h"
#include "Users/userdatadialog.h"
#include "NetworkAzs/networkazsdialog.h"

#include <QMessageBox>
#include <QLabel>

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
    QLabel *statusBarUser  = new QLabel();
    statusBarUser->setText(tr("Пользователь: ")+_currentUser->getUserFIO());
    ui->statusbar->addPermanentWidget(statusBarUser,1);
    QLabel *statusBarLang = new QLabel();
    statusBarLang->setText(tr("Язык интерфейса: ")+_currentUser->getLangName());
    ui->statusbar->addPermanentWidget(statusBarLang,4);

}

void MainWindow::on_actionUser_triggered()
{
    //Данные пользователя
    UserDataDialog *userDlg = new UserDataDialog(_currentUser->getUserID(),this);
    userDlg->exec();
}


void MainWindow::on_actionNetworkAzs_triggered()
{
    //Список сетей АЗС
    NetworkAzsDialog *netwAzs = new NetworkAzsDialog();
    netwAzs->exec();

}

