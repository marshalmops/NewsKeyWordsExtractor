#include "NewsParserStandardRSS.h"

namespace {

bool readPropertyFromXmlStream(const QString &propName,
                               QXmlStreamReader &xmlStream,
                               QString &content)
{
    if (propName.isEmpty()) return false;
    
    if (xmlStream.readNext() != QXmlStreamReader::TokenType::StartElement)
        return false;
    
    if (xmlStream.name() != propName) return false;
    
    content = xmlStream.readElementText();
    
    return true;
}

}

NewsParserStandardRSS::NewsParserStandardRSS()
    : NewsParserBase{SourceDictionary::SourceType::ST_STANDARD_RSS}
{
    
}

bool NewsParserStandardRSS::parseData(const RawNewsDataBase &data, 
                                      std::vector<News> &news)
{
    auto dataBytes = data.getData();
    std::vector<News> newsBuffer{};
    
    QXmlStreamReader rssReader{dataBytes};
    
    while (!rssReader.atEnd()) {
        if (rssReader.readNext() != QXmlStreamReader::TokenType::StartElement) continue;
        if (rssReader.name() != C_ITEM_TAG_NAME)                               continue;
        
        QString newsTitle{};
        
        if (!readPropertyFromXmlStream(C_NEWS_TITLE_PROP_NAME, rssReader, newsTitle))
            return false;
        
        QString newsDescription{};
        
        if (!readPropertyFromXmlStream(C_NEWS_DESCRIPTION_PROP_NAME, rssReader, newsTitle))
            return false;
        
        newsBuffer.push_back(News{newsDescription, newsTitle});
    }
    
    if (rssReader.hasError()) return false;
    
    news = std::move(newsBuffer);
    
    return true;
}
