#include "NewsParserTelegram.h"

NewsParserTelegram::NewsParserTelegram()
    : NewsParserBase{AppContext::SourceType::ST_TELEGRAM}
{
    
}

NewsParserBase::ParsingResult NewsParserTelegram::parseData(const RawNewsDataBase &data, 
                                                            News &news)
{
    // parsing Telegram JSON data...
}
