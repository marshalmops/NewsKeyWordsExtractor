#include "SourceListWidget.h"

template<class SourceType>
SourceListWidget<SourceType>::SourceListWidget(QWidget *parent)
    : QListView{parent},
      m_modelPtr{new SourceListModel{this}}
{
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    setModel(m_modelPtr);
}

template<class SourceType>
AppContext::Id SourceListWidget<SourceType>::getLastSelectedSourceId() const
{
    return m_modelPtr->getSourceIdByRow(m_lastSelectedItemIndex);
}

template<class SourceType>
bool SourceListWidget<SourceType>::removeLastSelectedSourceRow()
{
    return m_modelPtr->removeRows(m_lastSelectedItemIndex, 1);
}

template<class SourceType>
bool SourceListWidget<SourceType>::insertSourceRow()
{
    return m_modelPtr->insertRows(m_modelPtr->rowCount(), 1);
}

template<class SourceType>
void SourceListWidget<SourceType>::selectedSourceChanged()
{
    m_lastSelectedItemIndex = currentIndex().row();
}
