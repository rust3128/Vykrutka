#ifndef POSLISTWIDGET_H
#define POSLISTWIDGET_H
#include "ServicedObjects/createconnectionlist.h"
#include "ServicedObjects/statuspos.h"

#include <QWidget>

namespace Ui {
class PosListWidget;
}

class PosListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PosListWidget(uint tID, uint netID, QWidget *parent = nullptr);
    ~PosListWidget();
private slots:
    void slotPbVNCClicked();
    void slotStartTestVNC();
    void slotFinishTestVNC();
    void slotGetStatusVNC(StatusPos statPos);
private:
    void createUI();
private:
    Ui::PosListWidget *ui;
    uint terminalID;
    uint networkID;
    StatusPos statusPos;
    CreateConnectionList *conn;
    QList<QStringList> connList;
    uint columnCount;

};

#endif // POSLISTWIDGET_H
