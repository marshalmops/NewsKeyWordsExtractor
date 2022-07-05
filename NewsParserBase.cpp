#include "NewsParserBase.h"
  
NewsParserBase::NewsParserBase(const SourceDictionary::SourceType sourceType)
    : m_sourceType{sourceType}
{
    
}

SourceDictionary::SourceType NewsParserBase::getSourceType() const
{
    return m_sourceType;
}
