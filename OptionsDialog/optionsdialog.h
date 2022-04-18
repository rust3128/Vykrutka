#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(bool isNew, QWidget *parent = nullptr);
    ~OptionsDialog();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_toolButtonBroseVNC_clicked();

private:
    void createUI();
    void writeOptions();
    void readOptions();
private:
    Ui::OptionsDialog *ui;
    bool isNewConfig;
};

#endif // OPTIONSDIALOG_H
