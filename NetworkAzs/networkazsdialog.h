#ifndef NETWORKAZSDIALOG_H
#define NETWORKAZSDIALOG_H

#include "modelnetworkazs.h"
#include "logodelegate.h"

#include <QDialog>

namespace Ui {
class NetworkAzsDialog;
}

class NetworkAzsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkAzsDialog(QWidget *parent = nullptr);
    ~NetworkAzsDialog();

private slots:
    void on_checkBoxShowServers_clicked();
    void on_pushButtonAdd_clicked();

    void on_tableViewNetworks_doubleClicked(const QModelIndex &idx);

private:
    void createUI();
    void createModels();
private:
    Ui::NetworkAzsDialog *ui;
    ModelNetworkAzs *modelNetwork;
    LogoDelegate *logoDelegate;
};

#endif // NETWORKAZSDIALOG_H
