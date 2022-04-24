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

}

void EditNetworkAzsDialog::createUI()
{
    currentNetwork = new NetworkAzsData(networkID);
    ui->lineEditName->setText(currentNetwork->getNetworkName());
    ui->checkBoxIsActive->setChecked(currentNetwork->getIsActive());
}

