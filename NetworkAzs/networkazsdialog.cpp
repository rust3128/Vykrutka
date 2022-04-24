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

    createUI();
}

NetworkAzsDialog::~NetworkAzsDialog()
{
    delete ui;
}

void NetworkAzsDialog::createUI()
{
    ui->groupBoxServers->hide();
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

