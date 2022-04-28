#include "modelnetworkazs.h"

ModelNetworkAzs::ModelNetworkAzs(QObject *parent)
    : QSqlQueryModel{parent}
{

}


QVariant ModelNetworkAzs::data(const QModelIndex &idx, int role) const
{
    return QSqlQueryModel::data(idx,role);
}
