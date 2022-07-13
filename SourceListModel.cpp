#include "SourceListModel.h"

bool SourceListModel::isDataInputsCorrect(const QModelIndex &index, 
                                          int role,
                                          int count) const
{
    if (!index.isValid()) return false;
    
    if (role != Qt::DisplayRole && role < SourceListModel::SourceListModelRoles::SLMR_SOURCE_ID)
        return false;
    
    if (count <= index.row()) return false;
    
    return true;
}

SourceListModel::SourceListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    
}

bool SourceListModel::insertRows(int row, 
                                 int count, 
                                 const QModelIndex &parent)
{
    if (parent.isValid() || row > rowCount()) return false;
    
    emit beginInsertRows(parent, row, row + count - 1);
    emit endInsertRows();
    
    return true;
}

bool SourceListModel::removeRows(int row,
                                 int count,
                                 const QModelIndex &parent)
{
    if (parent.isValid() || row > rowCount()) return false;
    
    emit beginRemoveRows(parent, row, row + count - 1);
    emit endRemoveRows();
    
    return true;
}

AppContext::Id SourceListModel::getSourceIdByRow(const int row) const
{
    QVariant sourceIdVariant = data(index(row, 0), SourceListModel::SourceListModelRoles::SLMR_SOURCE_ID);
    
    if (sourceIdVariant.isNull()) return 0;
    
    return sourceIdVariant.toULongLong();
}


