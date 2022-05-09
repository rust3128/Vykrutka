#ifndef VNCBUTTON_H
#define VNCBUTTON_H

#include <QToolButton>

class VncButton : public QToolButton
{
public:
    explicit VncButton(uint posID, QWidget *parent = nullptr);
    uint getButtonID() const;

private:
    uint buttonID=0;
};

#endif // VNCBUTTON_H
