#ifndef EDITNETWORKAZSDIALOG_H
#define EDITNETWORKAZSDIALOG_H

#include <QDialog>

namespace Ui {
class EditNetworkAzsDialog;
}

class EditNetworkAzsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditNetworkAzsDialog(QWidget *parent = nullptr);
    ~EditNetworkAzsDialog();

private slots:
    void on_toolButton_clicked();

private:
    Ui::EditNetworkAzsDialog *ui;
    QByteArray inByteArray;
};

#endif // EDITNETWORKAZSDIALOG_H
