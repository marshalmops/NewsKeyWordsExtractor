#include "NewsParserTelegram.h"

NewsParserTelegram::NewsParserTelegram()
    : NewsParserBase{SourceDictionary::SourceType::ST_TELEGRAM}
{
    
}

std::vector<News> &&NewsParserTelegram::parseData(const RawNewsDataBase &data)
{
    // parsing Telegram JSON data...
}
