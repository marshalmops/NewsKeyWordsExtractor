#ifndef NEWSPARSERSTANDARDRSS_H
#define NEWSPARSERSTANDARDRSS_H

#include <QRegExp>
#include <qgumbodocument.h>
#include <qgumbonode.h>

#include "AppContext.h"
#include "NewsParserBase.h"

#include "SourceStandardRSS.h"

class NewsParserStandardRSS : public NewsParserBase
{
    constexpr static const char* C_ITEM_TAG_NAME = "item";
    
public:
    NewsParserStandardRSS();
    
    virtual ParsingResult parseData(const RawNewsDataBase &data,
                                    News &news) override;
};

#endif // NEWSPARSERSTANDARDRSS_H
