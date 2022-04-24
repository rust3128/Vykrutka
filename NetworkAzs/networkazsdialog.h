#ifndef NETWORKAZSDIALOG_H
#define NETWORKAZSDIALOG_H

#include <QDialog>

namespace Ui {
class NetworkAzsDialog;
}

class NetworkAzsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkAzsDialog(QWidget *parent = nullptr);
    ~NetworkAzsDialog();

private slots:
    void on_checkBoxShowServers_clicked();

    void on_pushButtonAdd_clicked();

private:
    void createUI();
private:
    Ui::NetworkAzsDialog *ui;
};

#endif // NETWORKAZSDIALOG_H
