#include "SourceListModel.h"

namespace {

template<class SourceType>
bool isDataInputsCorrect(const QModelIndex &index, 
                         int role,
                         int count)
{
    if (!index.isValid()) return false;
    
    if (role != Qt::DisplayRole && role < SourceListModel<SourceType>::SourceListModelRoles::SLMR_SOURCE_ID)
        return false;
    
    if (count <= index.row()) return false;
    
    return true;
}

}

template<class SourceType>
SourceListModel<SourceType>::SourceListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    
}

template<class SourceType>
int SourceListModel<SourceType>::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return -1;
    
    return SourceDictionary::getSources()->size();
}

template<>
QVariant SourceListModel<SourceStandardRSS>::data(const QModelIndex &index, 
                               int role) const
{
    if (!isDataInputsCorrect<SourceStandardRSS>(index, role, rowCount()))
        return QVariant{};
    
    const auto &sources = SourceDictionary::getSources();
    const auto *curElem = dynamic_cast<SourceStandardRSS*>(&(sources->at(index.row())));
    
    switch (role) {
    case Qt::DisplayRole: {
        return curElem->getBaseUrl();
    }
    case SourceListModelRoles::SLMR_SOURCE_ID: {
        return curElem->getId();
    }
    }
    
    return QVariant{};
}

template<>
QVariant SourceListModel<SourceTelegram>::data(const QModelIndex &index, 
                               int role) const
{
    if (!isDataInputsCorrect<SourceTelegram>(index, role, rowCount()))
        return QVariant{};
    
    const auto &sources = SourceDictionary::getSources();
    const auto *curElem = dynamic_cast<SourceTelegram*>(&(sources->at(index.row())));
    
    switch (role) {
    case Qt::DisplayRole: {
        return curElem->getChannelName();
    }
    case SourceListModelRoles::SLMR_SOURCE_ID: {
        return curElem->getId();
    }
    }
    
    return QVariant{};
}

template<class SourceType>
QVariant SourceListModel<SourceType>::data(const QModelIndex &index, 
                                           int role) const
{
    return QVariant{};
}

template<class SourceType>
bool SourceListModel<SourceType>::insertRows(int row, 
                                             int count, 
                                             const QModelIndex &parent)
{
    if (parent.isValid() || row >= rowCount()) return false;
    
    emit beginInsertRows(parent, row, row + count - 1);
    emit endInsertRows();
    
    return true;
}

template<class SourceType>
bool SourceListModel<SourceType>::removeRows(int row,
                                             int count,
                                             const QModelIndex &parent)
{
    if (parent.isValid() || row >= rowCount()) return false;
    
    emit beginRemoveRows(parent, row, row + count - 1);
    emit endRemoveRows();
    
    return true;
}

template<class SourceType>
AppContext::Id SourceListModel<SourceType>::getSourceIdByRow(const int row) const
{
    QVariant sourceIdVariant = data(index(row, 0));
    
    if (sourceIdVariant.isNull()) return 0;
    
    return sourceIdVariant.toULongLong();
}


