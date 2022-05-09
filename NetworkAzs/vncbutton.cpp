#include "vncbutton.h"

VncButton::VncButton(uint posID, QWidget *parent) :
    QToolButton(parent)
{
    buttonID = posID;
}

uint VncButton::getButtonID() const
{
    return buttonID;
}
