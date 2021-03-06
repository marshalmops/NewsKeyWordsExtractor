#include "NewsParserStandardRSS.h"
#include "qdebug.h"

NewsParserStandardRSS::NewsParserStandardRSS()
    : NewsParserBase{AppContext::SourceType::ST_STANDARD_RSS}
{
    
}

NewsParserBase::ParsingResult NewsParserStandardRSS::parseData(const RawNewsDataBase &data, 
                                      News &news)
{
    QGumboDocument dataHtmlPage{QGumboDocument::parse(data.getData())};
    auto root = dataHtmlPage.rootNode();

    QString textContainerClassName{dynamic_cast<SourceStandardRSS*>(data.getSource().get())->getArticleTextClassName()};
    auto textNodes = root.getElementsByClassName(textContainerClassName); 
    
    QString newsContent{};
    
    for (auto i = textNodes.begin(); i != textNodes.end(); ++i) {
        newsContent += i->innerText();
    }
    
    if (newsContent.isEmpty()) return NewsParserBase::ParsingResult::PR_NO_DATA;
    
    news = News{std::move(newsContent)};
    
    return NewsParserBase::ParsingResult::PR_SUCCESS;
}
