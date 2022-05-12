#include "testtemplatedialog.h"
#include "ui_testtemplatedialog.h"
#include "LoggingCategories/loggingcategories.h"

#include "VncConnect/testvncconnect.h"

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



//    for(uint i = 0;i<rowCount; ++i){

//        QGroupBox *groupBoxPos = new QGroupBox("Pos ID "+QString::number(i+1),this);
//        QHBoxLayout *grBoxLayout = new QHBoxLayout();
//        QLineEdit *lineEdit = new QLineEdit();
//        labelStatus = new QLabel();
//        grBoxLayout->addWidget(labelStatus);
//        lineEdit->setText(connList.at(i).at(0)+":"+connList.at(i).at(1));
//        grBoxLayout->addWidget(lineEdit);
//        vncButton = new VncButton(i,this);
//        vncButton->setIcon(QIcon(":/Images/TightVNC_logo.png"));
//        vncButton->setIconSize(QSize(32,32));
//        grBoxLayout->addWidget(vncButton);
//        groupBoxPos->setLayout(grBoxLayout);
//        ui->gridLayout->addWidget(groupBoxPos);
//        connect(vncButton,&QAbstractButton::clicked,this,&TestTemplateDialog::slotVncConnect);

//        TestVNCConnect *testVNC = new TestVNCConnect(connList.at(i).at(0), connList.at(i).at(1).toUInt());
//        QThread *thread = new QThread();
//        testVNC->moveToThread(thread);

//        connect(thread,&QThread::started,this,&TestTemplateDialog::slotStartTestVNC);
//        connect(thread,&QThread::started,testVNC,&TestVNCConnect::checkConnectionStatus);
//        connect(testVNC,&TestVNCConnect::signalSendStatusConnect,this,&TestTemplateDialog::slotGetStatusVNC);
//        connect(testVNC,&TestVNCConnect::finish,thread,&QThread::quit);
//        connect(testVNC,&TestVNCConnect::finish,this,&TestTemplateDialog::slotFinishTestVNC);
//        connect(testVNC,&TestVNCConnect::finish,testVNC,&TestVNCConnect::deleteLater);
//        connect(thread,&QThread::finished,thread,&QThread::deleteLater);

//        thread->start();


//    }
}



void TestTemplateDialog::on_buttonBox_rejected()
{
    this->reject();
}

void TestTemplateDialog::slotStartTestVNC()
{
    qInfo(logInfo()) << "Show testing" << labelStatus->indent();
    labelStatus->setPixmap(QPixmap(":/Images/connect_creating_icon.png").scaled(QSize(32,32)));
}

void TestTemplateDialog::slotFinishTestVNC()
{
//    qInfo(logInfo()) << "Show result.";
    if(statusVNC){
        labelStatus->setPixmap(QPixmap(":/Images/connect_established_icon.png").scaled(QSize(32,32)));
        vncButton->hide();
    } else {
        labelStatus->setPixmap(QPixmap(":/Images/connect_no_icon.png").scaled(QSize(32,32)));
        vncButton->show();
    }
}

void TestTemplateDialog::slotGetStatusVNC(bool status)
{
    statusVNC = status;
}

