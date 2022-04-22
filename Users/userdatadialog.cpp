#include "userdatadialog.h"
#include "ui_userdatadialog.h"
#include "LoggingCategories/loggingcategories.h"

#include <QSqlQuery>
#include <QSqlError>

UserDataDialog::UserDataDialog(int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDataDialog),
    userID(ID)
{
    ui->setupUi(this);
    currentUser = new Users(userID);
    createUI();
}

UserDataDialog::~UserDataDialog()
{
    delete ui;
}

void UserDataDialog::createUI()
{
    modelLang = new QSqlQueryModel();
    modelLang->setQuery("SELECT l.lang_id, l.lang_name from uilang l ORDER by l.lang_id");
    ui->comboBoxLangUI->setModel(modelLang);
    ui->comboBoxLangUI->setModelColumn(1);
    for(int i=0;i<modelLang->rowCount();++i){
        if(currentUser->getLangUI() == modelLang->data(modelLang->index(i,0)).toInt()){
            ui->comboBoxLangUI->setCurrentText(modelLang->data(modelLang->index(i,1)).toString());
            break;
        }
    }
    ui->lineEditLogin->setText(currentUser->getUserLogin());
    ui->lineEditFIO->setText(currentUser->getUserFIO());
    ui->lineEditAsterPhone->setText(currentUser->getAsterPhone());
    ui->lineEditMobPhone->setText(currentUser->getMobilePhone());
    ui->lineEditEmail->setText(currentUser->getEmail());
    ui->checkBoxIsActive->setChecked(currentUser->getIsActive());
}

void UserDataDialog::on_buttonBox_rejected()
{
    this->reject();
}


void UserDataDialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    q.prepare("UPDATE USERS SET USER_FIO = :fio, ASTER_PHONE = :aster, PHONE = :mobile, EMAIL = :email, UI_LANG = :lang, ISACTIBE = :isActive WHERE (USER_ID = :uID)");
    q.bindValue(":fio",ui->lineEditFIO->text().trimmed());
    q.bindValue(":aster",ui->lineEditAsterPhone->text().trimmed());
    q.bindValue(":mobile", ui->lineEditMobPhone->text().trimmed());
    q.bindValue(":email",ui->lineEditEmail->text().trimmed());
    q.bindValue(":isActive", QVariant(ui->checkBoxIsActive->isChecked()).toInt());

    q.bindValue(":lang",modelLang->data(modelLang->index(ui->comboBoxLangUI->currentIndex(),0)).toInt());
    q.bindValue(":uID",userID);

    if(!q.exec()){
        qCritical(logCritical()) << "User update error." << q.lastError().text();
        return;
    }
    this->accept();
}

