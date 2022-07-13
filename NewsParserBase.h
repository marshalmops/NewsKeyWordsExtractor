#ifndef NEWSPARSERBASE_H
#define NEWSPARSERBASE_H

#include "AppContext.h"

#include "RawNewsDataBase.h"
#include "News.h"

class NewsParserBase
{
public:
    enum ParsingResult : uint8_t {
        PR_NO_DATA = 0,
        PR_ERROR,
        PR_SUCCESS
    };
    
    NewsParserBase(const AppContext::SourceType sourceType);
    virtual ~NewsParserBase() = default;
    
    virtual ParsingResult parseData(const RawNewsDataBase &data,
                                    News &news) = 0;
    
    AppContext::SourceType getSourceType() const;
    
private:
    AppContext::SourceType m_sourceType;
};

#endif // NEWSPARSERBASE_H
