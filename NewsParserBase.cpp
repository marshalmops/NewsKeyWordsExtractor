#include "NewsParserBase.h"
  
NewsParserBase::NewsParserBase(const AppContext::SourceType sourceType)
    : m_sourceType{sourceType}
{
    
}

AppContext::SourceType NewsParserBase::getSourceType() const
{
    return m_sourceType;
}
