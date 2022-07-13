#ifndef NETWORKRESPONSEPREPARERVK_H
#define NETWORKRESPONSEPREPARERVK_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QCborMap>

#include "NetworkResponsePreparerBase.h"

class NetworkResponsePreparerVK : public NetworkResponsePreparerBase
{
    constexpr static const char* C_ERROR_PROP_NAME = "error";
    
    constexpr static const char* C_ITEMS_WRAPPER_PROP_NAME = "response";
    constexpr static const char* C_ITEMS_PROP_NAME         = "items";
    
public:
    NetworkResponsePreparerVK(const std::shared_ptr<NetworkRequestExecutor> &executor);
    
    virtual bool prepareResponse(const QByteArray &responseBytes, 
                                 std::vector<QByteArray> &preparedData) override;
};

#endif // NETWORKRESPONSEPREPARERVK_H
