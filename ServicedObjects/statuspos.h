#ifndef STATUSPOS_H
#define STATUSPOS_H


class StatusPos
{
public:
    StatusPos();
    unsigned int getPosID() const;
    void setPosID(unsigned int newPosID);

    bool getConnected() const;
    void setConnected(bool newConnected);

private:
    unsigned int PosID;
    bool connected;
};

#endif // STATUSPOS_H
