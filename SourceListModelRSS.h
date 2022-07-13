#ifndef SOURCELISTMODELRSS_H
#define SOURCELISTMODELRSS_H

#include <QObject>

#include "SourceListModel.h"

class SourceListModelRSS : public SourceListModel
{
    Q_OBJECT
public:
    explicit SourceListModelRSS(QObject *parent = nullptr);
    
    virtual QVariant data(const QModelIndex &index, 
                          int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
};

#endif // SOURCELISTMODELRSS_H
