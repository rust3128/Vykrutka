#include "testtemplatedialog.h"
#include "ui_testtemplatedialog.h"
#include "LoggingCategories/loggingcategories.h"
#include "ServicedObjects/poslistwidget.h"


#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>


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
    PosListWidget *widgetPosList = new PosListWidget(terminalID, networkID, this);
    ui->gridLayout->addWidget(widgetPosList);
    widgetPosList->show();
}



void TestTemplateDialog::on_buttonBox_rejected()
{
    this->reject();
}


