#include "NewsParserVK.h"

NewsParserVK::NewsParserVK()
    : NewsParserBase{SourceDictionary::SourceType::ST_VK}
{
    
}

std::vector<News> &&NewsParserVK::parseData(const RawNewsDataBase &data)
{
    // parsing VK JSON data...
}
