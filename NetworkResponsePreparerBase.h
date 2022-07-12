#ifndef NETWORKRESPONSEPREPARERBASE_H
#define NETWORKRESPONSEPREPARERBASE_H

#include "NetworkRequestExecutor.h"

class NetworkResponsePreparerBase
{
public:
    NetworkResponsePreparerBase(const std::shared_ptr<NetworkRequestExecutor> &executor);
    
    virtual bool prepareResponse(const QByteArray &responseBytes,
                                 std::vector<QByteArray> &preparedData) = 0;
    
protected:
    std::shared_ptr<NetworkRequestExecutor> m_executor;
};

#endif // NETWORKRESPONSEPREPARERBASE_H
