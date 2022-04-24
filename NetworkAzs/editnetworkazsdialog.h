#ifndef EDITNETWORKAZSDIALOG_H
#define EDITNETWORKAZSDIALOG_H

#include "NetworkAzs/networkazsdata.h"

#include <QDialog>


namespace Ui {
class EditNetworkAzsDialog;
}

class EditNetworkAzsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditNetworkAzsDialog(int ID, QWidget *parent = nullptr);
    ~EditNetworkAzsDialog();

private slots:
    void on_toolButton_clicked();
private:
    void createUI();
private:
    Ui::EditNetworkAzsDialog *ui;
    QByteArray inByteArray;
    int networkID;
    NetworkAzsData *currentNetwork;
};

#endif // EDITNETWORKAZSDIALOG_H
