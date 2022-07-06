#ifndef NEWSPARSERTELEGRAM_H
#define NEWSPARSERTELEGRAM_H

#include "NewsParserBase.h"

class NewsParserTelegram : public NewsParserBase
{
public:
    NewsParserTelegram();
    
    virtual bool parseData(const RawNewsDataBase &data,
                           std::vector<News> &news) override;
};

#endif // NEWSPARSERTELEGRAM_H
