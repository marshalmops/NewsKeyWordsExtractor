#ifndef SOURCELISTWIDGET_H
#define SOURCELISTWIDGET_H

#include <QObject>
#include <QListView>

#include "AppContext.h"

#include "SourceListModel.h"

class SourceListWidget : public QListView
{
    Q_OBJECT
public:
    explicit SourceListWidget(SourceListModel *model,
                              QWidget *parent = nullptr);
    
    int getLastSelectedItemIndex();
    AppContext::Id getLastSelectedSourceId() const;
    
public slots:
    bool removeLastSelectedSourceRow();
    bool insertSourceRow();
    
protected slots:
    void selectedSourceChanged(QModelIndex newIndex);
    
private:
    SourceListModel *m_modelPtr;
    
    int m_lastSelectedItemIndex;
};

#endif // SOURCELISTWIDGET_H
