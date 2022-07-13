#include "NewsParserVK.h"

NewsParserVK::NewsParserVK()
    : NewsParserBase{AppContext::SourceType::ST_VK}
{
    
}

NewsParserBase::ParsingResult NewsParserVK::parseData(const RawNewsDataBase &data, 
                                                      News &news)
{
    auto newsData = data.getData();
    
    if (newsData.isEmpty()) 
        return NewsParserBase::ParsingResult::PR_ERROR;
    
    QJsonDocument newsDataJson{QJsonDocument::fromJson(newsData)};
    QJsonObject   newsItemJson{newsDataJson.object()};
    
    if (newsItemJson.isEmpty()) 
        return NewsParserBase::ParsingResult::PR_ERROR;
    
    QString postType{};
    
    if (!getPostType(newsItemJson, postType))
        return NewsParserBase::ParsingResult::PR_ERROR;
    
    if (postType != C_POST_TYPE_PROP_VALUE)
        return NewsParserBase::ParsingResult::PR_NO_DATA;
    
    if (!newsItemJson.contains(C_POST_TEXT_PROP_NAME))
        return NewsParserBase::ParsingResult::PR_NO_DATA;
    
    if (!newsItemJson[C_POST_TEXT_PROP_NAME].isString())
        return NewsParserBase::ParsingResult::PR_NO_DATA;
    
    QString postText{newsItemJson[C_POST_TEXT_PROP_NAME].toString()};
    
    if (postText.isEmpty())
        return NewsParserBase::ParsingResult::PR_NO_DATA;
    
    news = News{postText};
    
    return NewsParserBase::ParsingResult::PR_SUCCESS;
}

bool NewsParserVK::getPostType(const QJsonObject &obj, 
                               QString &postType) const
{
    if (obj.isEmpty()) return false;
    
    static QStringList possiblePostTypePropNames = {"post_type", "type"};
    
    foreach (const auto &possiblePropName, possiblePostTypePropNames) {
        if (obj.contains(possiblePropName)) 
            if (obj[possiblePropName].isString()) {
                postType = obj[possiblePropName].toString();
                
                break;
            }
    }
    
    return !postType.isEmpty();
}

