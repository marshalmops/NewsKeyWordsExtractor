#ifndef NEWSPARSERSTANDARDRSS_H
#define NEWSPARSERSTANDARDRSS_H

#include "NewsParserBase.h"

class NewsParserStandardRSS : public NewsParserBase
{
public:
    NewsParserStandardRSS();
    
    virtual std::vector<News>&& parseData(const RawNewsDataBase &data) override;
};

#endif // NEWSPARSERSTANDARDRSS_H
