#include "CriptPass.h"

QString criptPass(QString str)
{

    QByteArray ba = str.toUtf8();
    return ba.toBase64();
}

QString decriptPass(QString str)
{
    QByteArray ba = str.toUtf8();
    return QByteArray::fromBase64(ba);
}
