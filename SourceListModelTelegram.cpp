#include "SourceListModelTelegram.h"

SourceListModelTelegram::SourceListModelTelegram(QObject *parent)
    : SourceListModel{parent}
{
    
}

int SourceListModelTelegram::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return -1;
    
    return SourceDictionary::getSourcesOfType(AppContext::SourceType::ST_TELEGRAM)->size();
}

QVariant SourceListModelTelegram::data(const QModelIndex &index, 
                                       int role) const
{
    if (!isDataInputsCorrect(index, role, rowCount()))
        return QVariant{};
    
    const auto &sources = SourceDictionary::getSourcesOfType(AppContext::SourceType::ST_TELEGRAM);
    const auto *curElem = dynamic_cast<SourceTelegram*>((sources->at(index.row())).get());
    
    if (!curElem) return QVariant{};
    
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
