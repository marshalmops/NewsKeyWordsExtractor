#ifndef NETWORKRESPONSEPREPARERRSS_H
#define NETWORKRESPONSEPREPARERRSS_H

#include <QRegularExpression>

#include "NetworkResponsePreparerBase.h"

class NetworkResponsePreparerRSS : public NetworkResponsePreparerBase
{
    constexpr static const char* C_LINK_TAG_OPENING = "<link>";
    constexpr static const char* C_LINK_TAG_ENDING  = "</link>";
    
public:
    NetworkResponsePreparerRSS(const std::shared_ptr<NetworkRequestExecutor> &executor);
    
    virtual bool prepareResponse(const QByteArray &responseBytes,
                                 std::vector<QByteArray> &preparedData) override;
};

#endif // NETWORKRESPONSEPREPARERRSS_H
