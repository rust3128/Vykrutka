#ifndef EDITNETWORKAZSDIALOG_H
#define EDITNETWORKAZSDIALOG_H

#include "NetworkAzs/networkazsdata.h"
#include "NetworkAzs/centraldb.h"
#include "NetworkAzs/templatehostname.h"

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
    void on_buttonBox_accepted();

    void on_lineEditDBCenterServer_textEdited(const QString &arg1);

    void on_lineEditDBCenterPort_textEdited(const QString &arg1);

    void on_lineEditDBCenterFileDB_textEdited(const QString &arg1);

    void on_lineEditDBCenterUser_textEdited(const QString &arg1);

    void on_lineEditDBCenterPass_textEdited(const QString &arg1);

    void on_buttonBox_rejected();

    void on_lineEditName_textEdited(const QString &arg1);

    void on_checkBoxIsActive_clicked();

    void on_checkBoxConnectFromTerm_clicked();

    void on_radioButtonUseTable_toggled(bool checked);


    void on_checkBoxPrefix_toggled(bool checked);

    void on_spinBoxMaxPOSID_valueChanged(int arg1);

    void on_radioButtonSingleVNCPort_toggled(bool checked);

    void on_spinBoxVNCPort_valueChanged(int arg1);

    void on_checkBoxCnangePrefix_toggled(bool checked);

    void on_radioButtonRangeVNCPorts_toggled(bool checked);

    void on_radioButtonUseTermID_toggled(bool checked);

    void on_radioButtonUseOwnerID_toggled(bool checked);

    void on_checkBoxChangeSufix_toggled(bool checked);

    void on_checkBoxSufix_toggled(bool checked);

    void on_lineEditPrefix_textEdited(const QString &arg1);

    void on_lineEditCnangePrefix_textEdited(const QString &arg1);

    void on_lineEditChangeSufix_textEdited(const QString &arg1);

    void on_lineEditSufix_textEdited(const QString &arg1);

    void on_pushButtonShowTemplate_clicked();

    void on_pushButtonDBCenterTest_clicked();

private:
    void createUI();
private:
    Ui::EditNetworkAzsDialog *ui;
    QByteArray inByteArray;
    int networkID;
    NetworkAzsData *currentNetwork;
    CentralDB *centralDB;
    TemplateHostname *tempHost;
};

#endif // EDITNETWORKAZSDIALOG_H
