#ifndef NEWSPARSERBASE_H
#define NEWSPARSERBASE_H

#include "SourceDictionary.h"

#include "RawNewsDataBase.h"
#include "News.h"

class NewsParserBase
{
public:
    NewsParserBase(const SourceDictionary::SourceType sourceType);
    virtual ~NewsParserBase() = default;
    
    virtual std::vector<News>&& parseData(const RawNewsDataBase &data) = 0;
    
    SourceDictionary::SourceType getSourceType() const;
    
private:
    SourceDictionary::SourceType m_sourceType;
};

#endif // NEWSPARSERBASE_H
