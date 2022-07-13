#ifndef PARSERDICTIONARY_H
#define PARSERDICTIONARY_H

#include "NewsParserBase.h"

#include "NewsParserStandardRSS.h"
#include "NewsParserTelegram.h"
#include "NewsParserVK.h"

class ParserDictionary
{
public:
    ParserDictionary() = delete;
    
    static NewsParserBase::ParsingResult parseData(const RawNewsDataBase &data,
                                                   News &news);
    
private:
    static std::unique_ptr<NewsParserBase> getParserBySourceType(const AppContext::SourceType sourceType);
};

#endif // PARSERDICTIONARY_H
