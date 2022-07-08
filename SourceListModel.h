#ifndef SOURCELISTMODEL_H
#define SOURCELISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "SourceDictionary.h"

template<class SourceType>
class SourceListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    enum SourceListModelRoles {
        SLMR_SOURCE_ID = Qt::UserRole + 1
    };
    
    explicit SourceListModel(QObject *parent = nullptr);
    
    virtual int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual QVariant data(const QModelIndex &index, 
                          int role) const override;
    
    virtual bool insertRows(int row, 
                            int count = 1, 
                            const QModelIndex &parent = QModelIndex{}) override;
    virtual bool removeRows(int row, 
                            int count = 1, 
                            const QModelIndex &parent = QModelIndex{}) override;

    AppContext::Id getSourceIdByRow(const int row) const;
};

#endif // SOURCELISTMODEL_H
