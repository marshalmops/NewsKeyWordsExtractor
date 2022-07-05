#include "SourceBase.h"

SourceBase::SourceBase()
    : m_url{}
{
    
}

SourceBase::SourceBase(const QUrl &url,
                       const std::shared_ptr<SourceContextInterface> &sourceContext)
    : m_url{url},
      m_sourceContext{sourceContext}
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
    if (!m_sourceContext.get() || !context.get()) return false;
    
    m_sourceContext = context;
    
    return true;
}
