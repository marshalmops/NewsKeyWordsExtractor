#include "NewsParserTelegram.h"

NewsParserTelegram::NewsParserTelegram()
    : NewsParserBase{SourceDictionary::SourceType::ST_TELEGRAM}
{
    
}

bool NewsParserTelegram::parseData(const RawNewsDataBase &data, 
                                   std::vector<News> &news)
{
    // parsing Telegram JSON data...
}
