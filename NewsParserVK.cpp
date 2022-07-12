#include "NewsParserVK.h"

NewsParserVK::NewsParserVK()
    : NewsParserBase{AppContext::SourceType::ST_VK}
{
    
}

bool NewsParserVK::parseData(const RawNewsDataBase &data, 
                             News &news)
{
//    std::vector<News> newsBuffer{};
    
//    QJsonDocument jsonData{QJsonDocument::fromJson(data.getData())};
    
//    if (jsonData.isObject()) return false;
    
//    QJsonObject rootObject{jsonData.object()};
    
//    if (!rootObject.contains(C_ITEMS_WRAPPER_PROP_NAME))   return false;
//    if (!rootObject[C_ITEMS_WRAPPER_PROP_NAME].isObject()) return false;
    
//    QJsonObject itemsWrapperObject{rootObject[C_ITEMS_WRAPPER_PROP_NAME].toObject()};
    
//    if (!itemsWrapperObject.contains(C_ITEMS_PROP_NAME))   return false;
//    if (!itemsWrapperObject[C_ITEMS_PROP_NAME].isArray()) return false;
    
//    QJsonArray itemsArray{itemsWrapperObject[C_ITEMS_PROP_NAME]};
    
//    foreach (const auto &item, itemsArray) {
//        if (!item.isObject()) return false;
        
//        QJsonObject curItemObject{item.toObject()};
        
//        if (!curItemObject.contains(C_POST_TYPE_PROP_NAME)
//         || !curItemObject.contains(C_POST_TEXT_PROP_NAME))
//        { 
//            return false;
//        }
        
//        if (!curItemObject[C_POST_TYPE_PROP_NAME].isString()
//         || !curItemObject[C_POST_TEXT_PROP_NAME].isString())
//        {
//            return false;
//        }
        
//        QString postType{curItemObject[C_POST_TYPE_PROP_NAME].toString()};
        
//        if (postType != C_POST_TYPE_PROP_VALUE) continue;
        
//        QString postText{curItemObject[C_POST_TEXT_PROP_NAME].toString()};
        
//        newsBuffer.push_back(News{postText});
//    }
    
//    news = std::move(newsBuffer);
    
    return true;
}
