#include "editnetworkazsdialog.h"
#include "ui_editnetworkazsdialog.h"
#include "LoggingCategories/loggingcategories.h"



#include <QFileDialog>
#include <QBuffer>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

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
}


void EditNetworkAzsDialog::on_buttonBox_accepted()
{
    if(currentNetwork->getIsChanges() || centralDB->getIsChanged()){
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

