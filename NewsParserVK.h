#ifndef NEWSPARSERVK_H
#define NEWSPARSERVK_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "NewsParserBase.h"

class NewsParserVK : public NewsParserBase
{
    constexpr static const char* C_POST_TEXT_PROP_NAME  = "text";
    constexpr static const char* C_POST_TYPE_PROP_VALUE = "post";
    
public:
    NewsParserVK();
    
    virtual ParsingResult parseData(const RawNewsDataBase &data,
                                    News &news) override;
    
private:
    bool getPostType(const QJsonObject &obj, 
                     QString &postType) const;
};

#endif // NEWSPARSERVK_H
