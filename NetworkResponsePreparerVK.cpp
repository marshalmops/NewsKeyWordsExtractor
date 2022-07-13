#include "NetworkResponsePreparerVK.h"

NetworkResponsePreparerVK::NetworkResponsePreparerVK(const std::shared_ptr<NetworkRequestExecutor> &executor)
    : NetworkResponsePreparerBase{executor}
{
    
}

bool NetworkResponsePreparerVK::prepareResponse(const QByteArray &responseBytes, 
                                                std::vector<QByteArray> &preparedData)
{
    if (responseBytes.isEmpty()) return false;
    
    QJsonDocument responseJson{QJsonDocument::fromJson(responseBytes)};
    QJsonObject   rootJson    {responseJson.object()};
    
    if (rootJson.isEmpty()) return false;
    
    if (rootJson.contains(C_ERROR_PROP_NAME)) return false;
    
    if (!rootJson.contains(C_ITEMS_WRAPPER_PROP_NAME))   return false;
    if (!rootJson[C_ITEMS_WRAPPER_PROP_NAME].isObject()) return false;
    
    QJsonObject responseObj{rootJson[C_ITEMS_WRAPPER_PROP_NAME].toObject()};
    
    if (!responseObj.contains(C_ITEMS_PROP_NAME)) 
        return false;
    if (!responseObj[C_ITEMS_PROP_NAME].isArray())
        return false;
    
    QJsonArray itemsArray = responseObj[C_ITEMS_PROP_NAME].toArray();
    std::vector<QByteArray> preparedDataBuffer{};
    
    foreach (const auto &item, itemsArray) {
        if (!item.isObject()) return false;
        
        QJsonObject curItemObject = item.toObject();
        
        preparedDataBuffer.push_back(QJsonDocument{curItemObject}.toJson());
    }
    
    if (preparedDataBuffer.empty()) 
        return false;
    
    preparedData = std::move(preparedDataBuffer);
    
    return true;
}
