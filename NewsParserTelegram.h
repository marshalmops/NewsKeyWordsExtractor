#ifndef NEWSPARSERTELEGRAM_H
#define NEWSPARSERTELEGRAM_H

#include "NewsParserBase.h"

class NewsParserTelegram : public NewsParserBase
{
public:
    NewsParserTelegram();
    
    virtual std::vector<News>&& parseData(const RawNewsDataBase &data) override;
};

#endif // NEWSPARSERTELEGRAM_H
