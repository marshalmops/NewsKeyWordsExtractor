#include "NetworkRequestCreator.h"

NetworkRequestCreator::NetworkRequestCreator(const std::shared_ptr<NetworkSourceContextPreparer> &sourcePreparer)
    : m_sourcePreparer{sourcePreparer}
{
    
}

bool NetworkRequestCreator::createRequestForRSSSource(SourceBase *source, 
                                                      QNetworkRequest &request)
{
    if (!source) return false;
    
    request = QNetworkRequest{source->getBaseUrl()};
    
    return true;
}

bool NetworkRequestCreator::createRequestForTelegramSource(SourceBase *source,
                                                           QNetworkRequest &request)
{
    if (!checkSourcePreparation(source)) return false;
    
    auto context = source->getContext(); 
    auto telegramContext = dynamic_cast<SourceContextTelegram*>(context.get()); // FIXME: not clear
    
    QUrl requestUrl{source->getBaseUrl()};
    
    // getting channel messages...
    
    
    
    return true;
}

bool NetworkRequestCreator::createRequestForVKSource(SourceBase *source, 
                                                     QNetworkRequest &request)
{
    if (!checkSourcePreparation(source)) return false;
    
    auto context = source->getContext(); 
    auto vkContext = dynamic_cast<SourceContextVK*>(context.get()); // FIXME: not clear
    
    QUrl requestUrl{source->getBaseUrl()};
    
    QUrlQuery getQuery{};
    
    getQuery.addQueryItem(SourceContextVK::C_TOKEN_PROPERTY,   vkContext->getToken());
    getQuery.addQueryItem(SourceContextVK::C_VERSION_PROPERTY, QString::number(SourceContextVK::C_VK_API_VERSION));
    
    requestUrl.setQuery(getQuery);
    request.setUrl(requestUrl);
    
    return true;
}

bool NetworkRequestCreator::createRequestForSource(SourceBase *source, 
                                                   QNetworkRequest &request)
{
    if (!source) return false;
    
    switch (source->getType()) {
    case AppContext::SourceType::ST_STANDARD_RSS: return createRequestForRSSSource(dynamic_cast<SourceStandardRSS*>(source), request);
    case AppContext::SourceType::ST_TELEGRAM:     return createRequestForTelegramSource(dynamic_cast<SourceTelegram*>(source), request);
    case AppContext::SourceType::ST_VK:           return createRequestForVKSource(dynamic_cast<SourceVK*>(source), request);
    }
    
    return false;
}

bool NetworkRequestCreator::checkSourcePreparation(SourceBase *source)
{
    if (!source) return false;
    if (!source->getContext()->isPrepared()) return false;
    if (!source->isPrepared()) return false;
    
    return true;
}
