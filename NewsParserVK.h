#ifndef NEWSPARSERVK_H
#define NEWSPARSERVK_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "NewsParserBase.h"

class NewsParserVK : public NewsParserBase
{
    constexpr static const char* C_ITEMS_WRAPPER_PROP_NAME = "response";
    constexpr static const char* C_ITEMS_PROP_NAME         = "items";
    
    constexpr static const char* C_POST_TYPE_PROP_NAME  = "post_type";
    constexpr static const char* C_POST_TYPE_PROP_VALUE = "post";
    
    constexpr static const char* C_POST_TEXT_PROP_NAME = "text";
    
public:
    NewsParserVK();
    
    virtual bool parseData(const RawNewsDataBase &data,
                           News &news) override;
};

#endif // NEWSPARSERVK_H
