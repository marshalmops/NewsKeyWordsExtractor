#include "NewsParserStandardRSS.h"


NewsParserStandardRSS::NewsParserStandardRSS()
    : NewsParserBase{SourceDictionary::SourceType::ST_STANDARD_RSS}
{
    
}

std::vector<News>&& NewsParserStandardRSS::parseData(const RawNewsDataBase &data)
{
    // RSS parsing...
}
