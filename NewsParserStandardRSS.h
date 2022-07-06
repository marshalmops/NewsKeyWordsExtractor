#ifndef NEWSPARSERSTANDARDRSS_H
#define NEWSPARSERSTANDARDRSS_H

#include <QXmlStreamReader>

#include "NewsParserBase.h"

class NewsParserStandardRSS : public NewsParserBase
{
    constexpr static const char* C_ITEM_TAG_NAME = "item";
    
    constexpr static const char* C_NEWS_TITLE_PROP_NAME       = "title";
    constexpr static const char* C_NEWS_DESCRIPTION_PROP_NAME = "description";
    
public:
    NewsParserStandardRSS();
    
    virtual bool parseData(const RawNewsDataBase &data,
                           std::vector<News> &news) override;
};

#endif // NEWSPARSERSTANDARDRSS_H
