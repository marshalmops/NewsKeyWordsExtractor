#include "ParserDictionary.h"

bool ParserDictionary::parseData(const RawNewsDataBase &data,
                                 std::vector<News> &news)
{
    auto parser = getParserBySourceType(data.getSourceType());
    
    news = parser->parseData(data);
    
    return !news.empty();
}

std::unique_ptr<NewsParserBase> ParserDictionary::getParserBySourceType(const SourceDictionary::SourceType sourceType)
{
    switch (sourceType) {
    case SourceDictionary::SourceType::ST_STANDARD_RSS: return std::make_unique<NewsParserStandardRSS>();
    case SourceDictionary::SourceType::ST_TELEGRAM:     return std::make_unique<NewsParserTelegram>();
    case SourceDictionary::SourceType::ST_VK:           return std::make_unique<NewsParserVK>();
    }
    
    return std::unique_ptr<NewsParserBase>{nullptr};
}
