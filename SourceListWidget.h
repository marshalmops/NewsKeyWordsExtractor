#ifndef SOURCELISTWIDGET_H
#define SOURCELISTWIDGET_H

#include <QObject>
#include <QListView>

#include "AppContext.h"

#include "SourceListModel.h"

template<class SourceType>
class SourceListWidget : public QListView
{
    Q_OBJECT
public:
    explicit SourceListWidget(QWidget *parent = nullptr);
    
    AppContext::Id getLastSelectedSourceId() const;
    
public slots:
    bool removeLastSelectedSourceRow();
    bool insertSourceRow();
    
protected slots:
    void selectedSourceChanged();
    
private:
    SourceListModel<SourceType> *m_modelPtr;
    
    int m_lastSelectedItemIndex;
};

#endif // SOURCELISTWIDGET_H
