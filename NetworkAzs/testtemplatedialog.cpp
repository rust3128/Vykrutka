#include "testtemplatedialog.h"
#include "ui_testtemplatedialog.h"
#include "LoggingCategories/loggingcategories.h"
#include "NetworkAzs/vncbutton.h"

#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QAbstractButton>

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

void TestTemplateDialog::slotVncConnect()
{
    VncButton *button = static_cast<VncButton*>(sender());
    const uint conID = button->getButtonID();

}

void TestTemplateDialog::createUI()
{
    conn = new CreateConnectionList(networkID, terminalID, this);
    connList = conn->getConnList();
    uint rowCount = connList.size();
    for(uint i = 0;i<rowCount; ++i){
        QGroupBox *groupBoxPos = new QGroupBox("Pos ID "+QString::number(i+1),this);
        QHBoxLayout *grBoxLayout = new QHBoxLayout();
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setText(connList.at(i).at(0)+":"+connList.at(i).at(1));
        grBoxLayout->addWidget(lineEdit);
        VncButton *vncButton = new VncButton(i,this);
        vncButton->setIcon(QIcon(":/Images/TightVNC_logo.png"));
        vncButton->setIconSize(QSize(32,32));
        grBoxLayout->addWidget(vncButton);
        groupBoxPos->setLayout(grBoxLayout);
        ui->gridLayout->addWidget(groupBoxPos);

        connect(vncButton,&QAbstractButton::clicked,this,&TestTemplateDialog::slotVncConnect);
    }
}



void TestTemplateDialog::on_buttonBox_rejected()
{
    this->reject();
}

