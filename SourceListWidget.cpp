#include "SourceListWidget.h"

SourceListWidget::SourceListWidget(SourceListModel *model,
                                   QWidget *parent)
    : QListView{parent},
      m_modelPtr{model}
{
    m_modelPtr->setParent(this);
    
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    setModel(m_modelPtr);
}

AppContext::Id SourceListWidget::getLastSelectedSourceId() const
{
    return m_modelPtr->getSourceIdByRow(m_lastSelectedItemIndex);
}

bool SourceListWidget::removeLastSelectedSourceRow()
{
    return m_modelPtr->removeRows(m_lastSelectedItemIndex, 1);
}

bool SourceListWidget::insertSourceRow()
{
    return m_modelPtr->insertRows(m_modelPtr->rowCount(), 1);
}

void SourceListWidget::selectedSourceChanged()
{
    m_lastSelectedItemIndex = currentIndex().row();
}
