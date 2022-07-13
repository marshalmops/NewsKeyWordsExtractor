#ifndef NEWSPARSERTELEGRAM_H
#define NEWSPARSERTELEGRAM_H

#include "NewsParserBase.h"

class NewsParserTelegram : public NewsParserBase
{
public:
    NewsParserTelegram();
    
    virtual ParsingResult parseData(const RawNewsDataBase &data,
                                    News &news) override;
};

#endif // NEWSPARSERTELEGRAM_H
