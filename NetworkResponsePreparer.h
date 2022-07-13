#ifndef NETWORKRESPONSEPREPARER_H
#define NETWORKRESPONSEPREPARER_H

#include "AppContext.h"

#include "NetworkResponsePreparerRSS.h"
#include "NetworkResponsePreparerVK.h"

class NetworkResponsePreparer
{
public:
    NetworkResponsePreparer(const std::shared_ptr<NetworkRequestExecutor> &executor);

    bool prepareResponse(AppContext::SourceType type,
                         const QByteArray &responseBytes,
                         std::vector<QByteArray> &preparedData);
    
private:
    std::shared_ptr<NetworkRequestExecutor> m_executor;
};

#endif // NETWORKRESPONSEPREPARER_H
