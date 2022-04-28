#include "networkazsdialog.h"
#include "ui_networkazsdialog.h"

#include "NetworkAzs/editnetworkazsdialog.h"
#include "LoggingCategories/loggingcategories.h"

#include <QInputDialog>
#include <QSqlQuery>
#include <QSqlError>

NetworkAzsDialog::NetworkAzsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkAzsDialog)
{
    ui->setupUi(this);

    createModels();
    createUI();
}

NetworkAzsDialog::~NetworkAzsDialog()
{
    delete ui;
}

void NetworkAzsDialog::createUI()
{
    //Наполнение интерефейса
    ui->groupBoxServers->hide();
    ui->tableViewNetworks->setModel(modelNetwork);
    ui->tableViewNetworks->setItemDelegateForColumn(2,logoDelegate);
//    ui->tableViewNetworks->verticalHeader()->hide();
    ui->tableViewNetworks->hideColumn(0);
    QHeaderView *headerView = ui->tableViewNetworks->horizontalHeader();
    headerView->swapSections(2, 1);
    ui->tableViewNetworks->resizeColumnToContents(1);
//    ui->tableViewNetworks->resizeColumnToContents(2);
    ui->tableViewNetworks->resizeColumnToContents(3);
    ui->tableViewNetworks->resizeColumnToContents(4);

}

void NetworkAzsDialog::createModels()
{
    //Создание моделей
    modelNetwork = new ModelNetworkAzs(this);
    logoDelegate = new LogoDelegate();
    modelNetwork->setQuery("select n.network_id, n.network_name, n.logo, n.type_connect, n.isactive from networkazs n ORDER by n.network_id");
    modelNetwork->setHeaderData(2,Qt::Horizontal,"Лого");
    modelNetwork->setHeaderData(1,Qt::Horizontal,"Наименование");
    modelNetwork->setHeaderData(3,Qt::Horizontal,"Подключение\nк АЗС");
    modelNetwork->setHeaderData(4,Qt::Horizontal,"В работе");

}

void NetworkAzsDialog::on_checkBoxShowServers_clicked()
{
    ui->groupBoxServers->setVisible(ui->checkBoxShowServers->isChecked());
}


void NetworkAzsDialog::on_pushButtonAdd_clicked()
{
    //Новая сеть АЗС

    bool ok;
    QString networkNew = QInputDialog::getText(this, tr("Новая сеть АЗС"), tr("Укажите наименование новой сети АЗС:"),
                                               QLineEdit::Normal,"",&ok);

    if (ok && networkNew.size() > 3) {
        QSqlQuery q;
        QString strSQL = QString("EXECUTE PROCEDURE add_networkazs('%1')")
                .arg(networkNew.trimmed());
        qInfo(logInfo()) << "strSQL" << strSQL;
        if(!q.exec(strSQL)){
            qCritical(logCritical()) << "Не удалось создать новую сеть АЗС" << q.lastError().text();
            return;
        }
        q.next();
        int _newNetworkID = q.value(0).toInt();
        q.exec("commit work");
        q.finish();
        EditNetworkAzsDialog *editNetDlg = new EditNetworkAzsDialog(_newNetworkID);
        editNetDlg->exec();
    }
}


void NetworkAzsDialog::on_tableViewNetworks_doubleClicked(const QModelIndex &idx)
{
    EditNetworkAzsDialog *editNetDlg = new EditNetworkAzsDialog(modelNetwork->data(modelNetwork->index(idx.row(),0),Qt::DisplayRole).toInt());
    editNetDlg->exec();
}

