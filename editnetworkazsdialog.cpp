#include "editnetworkazsdialog.h"
#include "ui_editnetworkazsdialog.h"

#include <QFileDialog>
#include <QBuffer>
#include <QMessageBox>

EditNetworkAzsDialog::EditNetworkAzsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditNetworkAzsDialog)
{
    ui->setupUi(this);
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

