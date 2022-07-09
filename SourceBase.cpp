#include "SourceBase.h"

SourceBase::SourceBase()
    : m_url{},
      m_sourceContext{nullptr},
      m_id{0}
{
    
}

SourceBase::SourceBase(const QUrl &url, 
                       const AppContext::Id id,
                       const std::shared_ptr<SourceContextInterface> &sourceContext)
    : m_url{url},
      m_sourceContext{sourceContext},
      m_id{id}
{
    
}

QUrl SourceBase::getBaseUrl() const
{
    return m_url;
}

std::shared_ptr<SourceContextInterface> SourceBase::getContext() const
{
    return m_sourceContext;
}

bool SourceBase::setContext(const std::shared_ptr<SourceContextInterface> &context)
{
    if (m_sourceContext.get() || !context.get()) return false;
    
    m_sourceContext = context;
    
    return true;
}

AppContext::Id SourceBase::getId() const
{
    return m_id;
}

bool SourceBase::setId(const AppContext::Id id)
{
    if (m_id > 0) return false;
    
    m_id = id;
    
    return true;
}
