#ifndef SOURCELISTMODEL_H
#define SOURCELISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "SourceDictionary.h"

class SourceListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    enum SourceListModelRoles {
        SLMR_SOURCE_ID = Qt::UserRole + 1
    };
    
    explicit SourceListModel(QObject *parent = nullptr);
    
    virtual bool insertRows(int row, 
                            int count = 1, 
                            const QModelIndex &parent = QModelIndex{}) override;
    virtual bool removeRows(int row, 
                            int count = 1, 
                            const QModelIndex &parent = QModelIndex{}) override;

    AppContext::Id getSourceIdByRow(const int row) const;
    
protected:
    bool isDataInputsCorrect(const QModelIndex &index, 
                             int role,
                             int count) const;
};

#endif // SOURCELISTMODEL_H
