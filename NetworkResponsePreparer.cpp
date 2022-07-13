#include "NetworkResponsePreparer.h"

NetworkResponsePreparer::NetworkResponsePreparer(const std::shared_ptr<NetworkRequestExecutor> &executor)
    : m_executor{executor}
{
    
}

bool NetworkResponsePreparer::prepareResponse(AppContext::SourceType type, 
                                              const QByteArray &responseBytes, 
                                              std::vector<QByteArray> &preparedData)
{
    if (type == AppContext::SourceType::ST_INVALID || responseBytes.isEmpty()) 
        return false;
    
    switch (type) {
    case AppContext::SourceType::ST_STANDARD_RSS: return std::make_unique<NetworkResponsePreparerRSS>(m_executor)->prepareResponse(responseBytes, preparedData);
    case AppContext::SourceType::ST_VK:           return std::make_unique<NetworkResponsePreparerVK>(m_executor)->prepareResponse(responseBytes, preparedData);
    default: preparedData.push_back(responseBytes);
    }
    
    return true;
}
