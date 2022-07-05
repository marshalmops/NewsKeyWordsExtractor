#ifndef NEWSPARSERVK_H
#define NEWSPARSERVK_H

#include "NewsParserBase.h"

class NewsParserVK : public NewsParserBase
{
public:
    NewsParserVK();
    
    virtual std::vector<News>&& parseData(const RawNewsDataBase &data) override;
};

#endif // NEWSPARSERVK_H
