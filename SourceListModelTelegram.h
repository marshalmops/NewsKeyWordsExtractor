#ifndef SOURCELISTMODELTELEGRAM_H
#define SOURCELISTMODELTELEGRAM_H

#include <QObject>

#include "SourceListModel.h"

class SourceListModelTelegram : public SourceListModel
{
    Q_OBJECT
public:
    explicit SourceListModelTelegram(QObject *parent = nullptr);
    
    virtual QVariant data(const QModelIndex &index, 
                          int role) const override;
};

#endif // SOURCELISTMODELTELEGRAM_H
