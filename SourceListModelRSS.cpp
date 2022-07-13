#include "SourceListModelRSS.h"

SourceListModelRSS::SourceListModelRSS(QObject *parent)
    : SourceListModel{parent}
{
    
}

int SourceListModelRSS::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return -1;
    
    return SourceDictionary::getSourcesOfType(AppContext::SourceType::ST_STANDARD_RSS)->size();
}

QVariant SourceListModelRSS::data(const QModelIndex &index, 
                                  int role) const
{
    if (!isDataInputsCorrect(index, role, rowCount()))
        return QVariant{};
    
    const auto &sources = SourceDictionary::getSourcesOfType(AppContext::SourceType::ST_STANDARD_RSS);
    const auto *curElem = dynamic_cast<SourceStandardRSS*>((sources->at(index.row())).get());
    
    if (!curElem) return QVariant{};
    
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
