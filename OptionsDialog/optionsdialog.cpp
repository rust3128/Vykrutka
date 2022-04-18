#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "GlobalSettings/globalsettings.h"
#include "OptionsDialog/CriptPass.h"

#include <QSettings>
#include <QFileDialog>
#include <QDir>

OptionsDialog::OptionsDialog(bool isNew, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog),
    isNewConfig(isNew)
{
    ui->setupUi(this);

    createUI();
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::createUI()
{
    if(isNewConfig){

    } else {
        readOptions();
    }
}

void OptionsDialog::writeOptions()
{
    QSettings settings(GlobalSettings::CONFIG_FILE_NAME, QSettings::IniFormat);
    settings.beginGroup("DATABASE");
    settings.setValue("Server",ui->lineEditServer->text().trimmed());
    settings.setValue("Port",ui->lineEditPort->text().trimmed());
    settings.setValue("DataBase", ui->lineEditDataBase->text().trimmed());
    settings.setValue("User",ui->lineEditUser->text().trimmed());
    settings.setValue("Password", criptPass(ui->lineEditPass->text().trimmed()));
    settings.endGroup();
    settings.beginGroup("COMMON");
    settings.setValue("VNCPath",ui->lineEditRunVNC->text().trimmed());
    settings.endGroup();

}

void OptionsDialog::readOptions()
{
    QSettings settings(GlobalSettings::CONFIG_FILE_NAME, QSettings::IniFormat);

    settings.beginGroup("DATABASE");
    ui->lineEditServer->setText(settings.value("Server").toString());
    ui->lineEditPort->setText(settings.value("Port").toString());
    ui->lineEditDataBase->setText(settings.value("DataBase").toString());
    ui->lineEditUser->setText(settings.value("User").toString());
    ui->lineEditPass->setText(decriptPass(settings.value("Password").toString()));
    settings.endGroup();
    settings.beginGroup("COMMON");
    ui->lineEditRunVNC->setText(settings.value("VNCPath").toString());
    settings.endGroup();

}

void OptionsDialog::on_buttonBox_rejected()
{
    this->reject();
}

void OptionsDialog::on_buttonBox_accepted()
{
    writeOptions();
    this->accept();
}

void OptionsDialog::on_toolButtonBroseVNC_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Выберите запускаемый файл VNC клиента."),
                                QDir::currentPath(),
                                "Программы (*.exe);;Все файлы (*.*)");
    ui->lineEditRunVNC->setText(fileName);

}

