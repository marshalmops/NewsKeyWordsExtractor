#ifndef NEWSPARSERBASE_H
#define NEWSPARSERBASE_H

#include "AppContext.h"

#include "RawNewsDataBase.h"
#include "News.h"

class NewsParserBase
{
public:
    NewsParserBase(const AppContext::SourceType sourceType);
    virtual ~NewsParserBase() = default;
    
    virtual bool parseData(const RawNewsDataBase &data,
                           News &news) = 0;
    
    AppContext::SourceType getSourceType() const;
    
private:
    AppContext::SourceType m_sourceType;
};

#endif // NEWSPARSERBASE_H
