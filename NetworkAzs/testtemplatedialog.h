#ifndef TESTTEMPLATEDIALOG_H
#define TESTTEMPLATEDIALOG_H
#include "NetworkAzs/templatehostname.h"
#include "NetworkAzs/centraldb.h"
#include "ServicedObjects/createconnectionlist.h"

#include <QDialog>

namespace Ui {
class TestTemplateDialog;
}

class TestTemplateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestTemplateDialog(uint tID, uint netID, QWidget *parent = nullptr);
    ~TestTemplateDialog();

private:
    void createUI();
private:
    Ui::TestTemplateDialog *ui;
    uint terminalID;
    uint networkID;
    CreateConnectionList *connList;
};

#endif // TESTTEMPLATEDIALOG_H
