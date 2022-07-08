#include "SourceListModelRSS.h"

SourceListModelRSS::SourceListModelRSS(QObject *parent)
    : SourceListModel{parent}
{
    
}

QVariant SourceListModelRSS::data(const QModelIndex &index, 
                                  int role) const
{
    if (!isDataInputsCorrect(index, role, rowCount()))
        return QVariant{};
    
    const auto &sources = SourceDictionary::getSources();
    const auto *curElem = dynamic_cast<SourceStandardRSS*>((sources->at(index.row())).get());
    
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
