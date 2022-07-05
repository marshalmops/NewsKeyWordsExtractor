#ifndef PARSERDICTIONARY_H
#define PARSERDICTIONARY_H

#include "NewsParserStandardRSS.h"
#include "NewsParserTelegram.h"
#include "NewsParserVK.h"

class ParserDictionary
{
public:
    ParserDictionary() = delete;
    
    static bool parseData(const RawNewsDataBase &data,
                          std::vector<News> &news);
    
private:
    static std::unique_ptr<NewsParserBase> getParserBySourceType(const SourceDictionary::SourceType sourceType);
};

#endif // PARSERDICTIONARY_H
