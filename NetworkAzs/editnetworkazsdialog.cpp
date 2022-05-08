#include "editnetworkazsdialog.h"
#include "ui_editnetworkazsdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include "NetworkAzs/testtemplatedialog.h"


#include <QFileDialog>
#include <QBuffer>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>

EditNetworkAzsDialog::EditNetworkAzsDialog(int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditNetworkAzsDialog),
    networkID(ID)
{
    ui->setupUi(this);

    createUI();
}

EditNetworkAzsDialog::~EditNetworkAzsDialog()
{
    delete ui;
}

void EditNetworkAzsDialog::on_toolButton_clicked()
{
    //Загрузка логотипа
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть логотип"), "", tr("Изображения (*.png *.jpeg *.jpg);;Все файлы (*.*)"),nullptr,QFileDialog::DontUseNativeDialog);
    QPixmap inPixmap(fileName); // Сохраняем его в изображение объекта QPixmap;

    if(inPixmap.width()>800 || inPixmap.height()>600){
        QMessageBox::warning(this, tr("Предупреждение"), tr("Внимание","Размер логотипа слишком большой. Выберите другой файл."));
        return;
    }

    ui->labelLogo->setPixmap(inPixmap);
    QBuffer inBuffer( &inByteArray );                   // Сохранение изображения производим через буффер
    inBuffer.open( QIODevice::WriteOnly );              // Открываем буффер
    inPixmap.save( &inBuffer, "PNG" );                  // Записываем inPixmap в inByteArray
    currentNetwork->setNetworkLogo(inByteArray);

}

void EditNetworkAzsDialog::createUI()
{
    currentNetwork = new NetworkAzsData(networkID);
    ui->lineEditName->setText(currentNetwork->getNetworkName());
    ui->checkBoxIsActive->setChecked(currentNetwork->getIsActive());
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(currentNetwork->getNetworkLogo());
    if(!outPixmap.isNull())
         ui->labelLogo->setPixmap(outPixmap);
    else
         ui->labelLogo->setText(tr("Логотип отсутствует"));

   //Центральная база данных
    centralDB = new CentralDB(networkID,this);
    ui->lineEditDBCenterServer->setText(centralDB->getServerName());
    ui->lineEditDBCenterPort->setText(QString::number(centralDB->getServerPort()));
    ui->lineEditDBCenterFileDB->setText(centralDB->getDatabaseFile());
    ui->lineEditDBCenterUser->setText(centralDB->getServerUser());
    ui->lineEditDBCenterPass->setText(centralDB->getUserPass());

    //Шаблон IP
    tempHost = new TemplateHostname(networkID,this);
    ui->checkBoxConnectFromTerm->setChecked(currentNetwork->getTypeConnect());
    switch (currentNetwork->getHostnameTypeGen()) {
    case 1:
        ui->radioButtonUseTable->setChecked(true);
        ui->groupBoxTemplateGen->hide();
        break;
    case 2:
        ui->radioButtonUseTemplate->setChecked(true);
        ui->groupBoxTemplateGen->show();
        break;
    default:
        break;
    }
    ui->spinBoxMaxPOSID->setValue(tempHost->getMaxPOSID());
    if(tempHost->getSingleVNCPort()){
        ui->radioButtonSingleVNCPort->setChecked(true);
    } else {
        ui->radioButtonRangeVNCPorts->setChecked(true);
    }

    ui->spinBoxVNCPort->setValue(tempHost->getVNCPort());
    if(tempHost->getPrefix().isEmpty()){
        ui->checkBoxPrefix->setChecked(false);
        ui->lineEditPrefix->hide();
    } else {
        ui->lineEditPrefix->show();
        ui->lineEditPrefix->setText(tempHost->getPrefix());
        ui->checkBoxPrefix->setChecked(true);
    }
    if(tempHost->getPrefixChange().isNull()){
        ui->checkBoxCnangePrefix->setChecked(false);
        ui->lineEditCnangePrefix->hide();
    } else {
        ui->checkBoxCnangePrefix->setChecked(true);
        ui->lineEditCnangePrefix->show();
        ui->lineEditCnangePrefix->setText(tempHost->getPrefixChange());
    }
    if(tempHost->getUseTermID()){
        ui->radioButtonUseTermID->setChecked(true);
    } else {
        ui->radioButtonUseOwnerID->setChecked(true);
    }
    if(tempHost->getSufixChange().isNull()){
        ui->checkBoxChangeSufix->setChecked(false);
        ui->lineEditChangeSufix->hide();
    } else {
        ui->checkBoxChangeSufix->setChecked(true);
        ui->lineEditChangeSufix->show();
        ui->lineEditChangeSufix->setText(tempHost->getSufixChange());
    }
    if(tempHost->getSufix().isEmpty()){
        ui->checkBoxSufix->setChecked(false);
        ui->lineEditSufix->hide();
    } else {
        ui->lineEditSufix->setText(tempHost->getSufix());
        ui->lineEditSufix->show();
        ui->checkBoxSufix->setChecked(true);
    }


}


void EditNetworkAzsDialog::on_buttonBox_accepted()
{
    if(currentNetwork->getIsChanges() || centralDB->getIsChanged() || tempHost->getIsChange()) {
        //Были изменения в данных по сети АЗС
        int result = QMessageBox::question(this,tr("Внимание"),
                                           QString(tr("Информация о клиенте %1 была изменена.\nВы дейстиветльно хотите обновить информацию в базе данных?"))
                                           .arg(ui->lineEditName->text().trimmed()));
        if(result == QMessageBox::Yes){
           if(currentNetwork->getIsChanges()){
                currentNetwork->saveData();
           }
           if(centralDB->getIsChanged()){
                centralDB->updateDB();
           }
           if(tempHost->getIsChange()){
               tempHost->saveToDB();
           }
        }
    }
    this->accept();
}




void EditNetworkAzsDialog::on_lineEditDBCenterServer_textEdited(const QString &arg1)
{
    centralDB->setServerName(arg1);
}


void EditNetworkAzsDialog::on_lineEditDBCenterPort_textEdited(const QString &arg1)
{
    centralDB->setServerPort(arg1.toInt());
}


void EditNetworkAzsDialog::on_lineEditDBCenterFileDB_textEdited(const QString &arg1)
{
    centralDB->setDatabaseFile(arg1);
}


void EditNetworkAzsDialog::on_lineEditDBCenterUser_textEdited(const QString &arg1)
{
    centralDB->setServerUser(arg1);
}


void EditNetworkAzsDialog::on_lineEditDBCenterPass_textEdited(const QString &arg1)
{
    centralDB->setUserPass(arg1);
}


void EditNetworkAzsDialog::on_buttonBox_rejected()
{
    this->reject();
}


void EditNetworkAzsDialog::on_lineEditName_textEdited(const QString &arg1)
{
    currentNetwork->setNetworkName(arg1);
}


void EditNetworkAzsDialog::on_checkBoxIsActive_clicked()
{
    currentNetwork->setIsActive(ui->checkBoxIsActive->isCheckable());
}


void EditNetworkAzsDialog::on_checkBoxConnectFromTerm_clicked()
{
    currentNetwork->setTypeConnect(ui->checkBoxConnectFromTerm->isChecked());
}


void EditNetworkAzsDialog::on_radioButtonUseTable_toggled(bool checked)
{
    if(checked){
        ui->groupBoxTemplateGen->hide();
        currentNetwork->setHostnameTypeGen(1);
    } else {
        ui->groupBoxTemplateGen->show();
        currentNetwork->setHostnameTypeGen(2);
    }
}

void EditNetworkAzsDialog::on_checkBoxPrefix_toggled(bool checked)
{
    ui->lineEditPrefix->setVisible(checked);
    if(!checked){
        tempHost->setPrefix("");
    }
}


void EditNetworkAzsDialog::on_spinBoxMaxPOSID_valueChanged(int arg1)
{
    tempHost->setMaxPOSID(arg1);
}


void EditNetworkAzsDialog::on_radioButtonSingleVNCPort_toggled(bool checked)
{
    tempHost->setSingleVNCPort(checked);
}


void EditNetworkAzsDialog::on_spinBoxVNCPort_valueChanged(int arg1)
{
    tempHost->setVNCPort(arg1);
}


void EditNetworkAzsDialog::on_checkBoxCnangePrefix_toggled(bool checked)
{
    ui->lineEditCnangePrefix->setVisible(checked);
    if(!checked){
        tempHost->setPrefixChange(QChar());
    }
}


void EditNetworkAzsDialog::on_radioButtonRangeVNCPorts_toggled(bool checked)
{
    tempHost->setSingleVNCPort(!checked);
}


void EditNetworkAzsDialog::on_radioButtonUseTermID_toggled(bool checked)
{
    tempHost->setUseTermID(checked);
}


void EditNetworkAzsDialog::on_radioButtonUseOwnerID_toggled(bool checked)
{
    tempHost->setUseTermID(!checked);
}


void EditNetworkAzsDialog::on_checkBoxChangeSufix_toggled(bool checked)
{
    ui->lineEditChangeSufix->setVisible(checked);
    if(!checked){
        tempHost->setSufixChange(QChar());
    }
}


void EditNetworkAzsDialog::on_checkBoxSufix_toggled(bool checked)
{
    ui->lineEditSufix->setVisible(checked);
    if(!checked){
        tempHost->setSufix("");
    }
}


void EditNetworkAzsDialog::on_lineEditPrefix_textEdited(const QString &arg1)
{
    tempHost->setPrefix(arg1);
}


void EditNetworkAzsDialog::on_lineEditCnangePrefix_textEdited(const QString &arg1)
{
    tempHost->setPrefixChange(arg1.at(0));
}


void EditNetworkAzsDialog::on_lineEditChangeSufix_textEdited(const QString &arg1)
{
    tempHost->setSufixChange(arg1.at(0));
}


void EditNetworkAzsDialog::on_lineEditSufix_textEdited(const QString &arg1)
{
    tempHost->setSufix(arg1);
}


void EditNetworkAzsDialog::on_pushButtonShowTemplate_clicked()
{
    tempHost->saveToDB();

    bool ok;
    int termID = QInputDialog::getInt(this, tr("Проврека шаблона"),
                                 tr("Введите номер терминала для проверки шаблона"), 1001, 1001, 99999, 1, &ok);
    if (ok){
        TestTemplateDialog *testTempl = new TestTemplateDialog(termID, networkID, this);
        testTempl->exec();
    }


}

void EditNetworkAzsDialog::on_pushButtonDBCenterTest_clicked()
{
    if(centralDB->getIsChanged()){
        int result = QMessageBox::question(this,tr("Внимание"),
                                           QString(tr("Информация о клиенте %1 была изменена.\nВы дейстиветльно хотите обновить информацию в базе данных?"))
                                           .arg(ui->lineEditName->text().trimmed()));
        if(result == QMessageBox::Yes){
            centralDB->updateDB();
        }
    }
    centralDB->createCentrDB();
    QSqlDatabase d = QSqlDatabase::database("centr");
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Диагностика подключения"));
    if(d.open()){
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(tr("Успешное подключение к базе данных!"));
        msgBox.setDetailedText(d.lastError().text());
    } else {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(tr("Ошибка подключения к базе данных!"));
        msgBox.setDetailedText(d.lastError().text());
    }
    msgBox.exec();

}

