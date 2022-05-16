#include "statuspos.h"

StatusPos::StatusPos()
{

}

unsigned int StatusPos::getPosID() const
{
    return PosID;
}

void StatusPos::setPosID(unsigned int newPosID)
{
    PosID = newPosID;
}

bool StatusPos::getConnected() const
{
    return connected;
}

void StatusPos::setConnected(bool newConnected)
{
    connected = newConnected;
}
