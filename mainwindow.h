#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Users/users.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Users *u, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionUser_triggered();

    void on_actionNetworkAzs_triggered();

private:
    void createUI();
private:
    Ui::MainWindow *ui;
    Users *_currentUser;

};
#endif // MAINWINDOW_H
