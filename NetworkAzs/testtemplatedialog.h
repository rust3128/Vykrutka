#ifndef TESTTEMPLATEDIALOG_H
#define TESTTEMPLATEDIALOG_H
#include "NetworkAzs/templatehostname.h"
#include "NetworkAzs/centraldb.h"
#include "ServicedObjects/createconnectionlist.h"
#include "NetworkAzs/vncbutton.h"

#include <QDialog>
#include <QAbstractButton>
#include <QLabel>

namespace Ui {
class TestTemplateDialog;
}

class TestTemplateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestTemplateDialog(uint tID, uint netID, QWidget *parent = nullptr);
    ~TestTemplateDialog();
private slots:
    void slotVncConnect();
    void on_buttonBox_rejected();
    void slotStartTestVNC();
    void slotFinishTestVNC();
    void slotGetStatusVNC(bool status);
private:
    void createUI();
private:
    Ui::TestTemplateDialog *ui;
    uint terminalID;
    uint networkID;
    CreateConnectionList *conn;
    QList<QStringList> connList;
    QLabel *labelStatus;
    VncButton *vncButton;
    bool statusVNC;

};

#endif // TESTTEMPLATEDIALOG_H
