#include "testtemplatedialog.h"
#include "ui_testtemplatedialog.h"

TestTemplateDialog::TestTemplateDialog(uint tID, uint netID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestTemplateDialog),
    terminalID(tID),
    networkID(netID)
{
    ui->setupUi(this);

    createUI();
}

TestTemplateDialog::~TestTemplateDialog()
{
    delete ui;
}

void TestTemplateDialog::createUI()
{
    connList = new CreateConnectionList(networkID, terminalID, this);
}


