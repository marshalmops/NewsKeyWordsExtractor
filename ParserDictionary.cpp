#include "ParserDictionary.h"

bool ParserDictionary::parseData(const RawNewsDataBase &data,
                                 News &news)
{
    auto parser = getParserBySourceType(data.getSource()->getType());
    
    return parser->parseData(data, news);
}

std::unique_ptr<NewsParserBase> ParserDictionary::getParserBySourceType(const AppContext::SourceType sourceType)
{
    switch (sourceType) {
    case AppContext::SourceType::ST_STANDARD_RSS: return std::make_unique<NewsParserStandardRSS>();
    case AppContext::SourceType::ST_TELEGRAM:     return std::make_unique<NewsParserTelegram>();
    case AppContext::SourceType::ST_VK:           return std::make_unique<NewsParserVK>();
    }
    
    return std::unique_ptr<NewsParserBase>{nullptr};
}
