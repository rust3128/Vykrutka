#include "poslistwidget.h"
#include "VncConnect/testvncconnect.h"
#include "ui_poslistwidget.h"
#include "LoggingCategories/loggingcategories.h"

#include <QPushButton>

PosListWidget::PosListWidget(uint tID, uint netID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PosListWidget),
    terminalID(tID),
    networkID(netID)
{
    ui->setupUi(this);
    createUI();
}

PosListWidget::~PosListWidget()
{
    delete ui;
}

void PosListWidget::slotPbVNCClicked()
{
    QWidget *w = qobject_cast<QWidget *>(sender()->parent());
    if(w){
        int row = ui->tableWidgetPosList->indexAt(w->pos()).row();
    }
}

void PosListWidget::createUI()
{
    conn = new CreateConnectionList(networkID, terminalID, this);
    connList = conn->getConnList();
    const uint rowCount = connList.size();
    QStringList headers = QStringList() << tr("PosID") << tr("Статус") << tr("Хост") << tr("Порт") << tr("Подключение");

    ui->tableWidgetPosList->setColumnCount(headers.size());
    ui->tableWidgetPosList->setRowCount(rowCount);
    for(uint row=0;row<rowCount;++row){
        ui->tableWidgetPosList->setItem(row,0, new QTableWidgetItem(QString::number(row+1)));
        ui->tableWidgetPosList->setItem(row,1, new QTableWidgetItem(QIcon(":/Images/connect_creating_icon.png"),""));
        ui->tableWidgetPosList->setItem(row,2, new QTableWidgetItem(connList.at(row).at(0)));
        ui->tableWidgetPosList->setItem(row,3, new QTableWidgetItem(connList.at(row).at(1)));

        QWidget* pWidget = new QWidget();
        QPushButton* btn_VNC = new QPushButton();
        btn_VNC->setIconSize(QSize(32,32));
        btn_VNC->setIcon(QIcon(":/Images/TightVNC_logo.png"));
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_VNC);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->tableWidgetPosList->setCellWidget(row, 4, pWidget);
        connect(btn_VNC,&QPushButton::clicked,this,&PosListWidget::slotPbVNCClicked);

        TestVNCConnect *testVNC = new TestVNCConnect(connList.at(row).at(0), connList.at(row).at(1).toUInt(),row);
        QThread *thread = new QThread();
        testVNC->moveToThread(thread);

        connect(thread,&QThread::started,this,&PosListWidget::slotStartTestVNC);
        connect(thread,&QThread::started,testVNC,&TestVNCConnect::checkConnectionStatus);
        connect(testVNC,&TestVNCConnect::signalSendStatusConnect,this,&PosListWidget::slotGetStatusVNC);
        connect(testVNC,&TestVNCConnect::finish,thread,&QThread::quit);
        connect(testVNC,&TestVNCConnect::finish,this,&PosListWidget::slotFinishTestVNC);
        connect(testVNC,&TestVNCConnect::finish,testVNC,&TestVNCConnect::deleteLater);
        connect(thread,&QThread::finished,thread,&QThread::deleteLater);

        thread->start();
    }
    ui->tableWidgetPosList->setHorizontalHeaderLabels(headers);
    ui->tableWidgetPosList->resizeColumnsToContents();
}



void PosListWidget::slotStartTestVNC()
{
    statusPos.setPosID(9999);
    statusPos.setConnected(false);
}

void PosListWidget::slotFinishTestVNC()
{
    QIcon iconStatus;
    if(statusPos.getConnected()){
        iconStatus = QIcon(":/Images/connect_established_icon.png");
    } else {
        iconStatus = QIcon(":/Images/connect_no_icon.png");
    }
    ui->tableWidgetPosList->item(statusPos.getPosID(),1)->setIcon(iconStatus);
    ui->tableWidgetPosList->cellWidget(statusPos.getPosID(),4)->setEnabled(statusPos.getConnected());
}

void PosListWidget::slotGetStatusVNC(StatusPos statPos)
{
    statusPos = statPos;
}
