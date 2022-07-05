#include "NetworkRequestExecutor.h"

NetworkRequestExecutor::NetworkRequestExecutor()
    : m_networkManager{}
{
    
}

bool NetworkRequestExecutor::executeGetRequest(const QNetworkRequest &request,
                                               QByteArray &reply)
{
    auto replyBuffer = m_networkManager.get(request);
    
    waitForResponse(replyBuffer);
    
    if (!replyBuffer->errorString().isEmpty() || replyBuffer->bytesAvailable() <= 0)
        return false;
    
    reply = replyBuffer->readAll();
    
    return true;
}

bool NetworkRequestExecutor::executePostRequest(const QNetworkRequest &request,
                                                const QByteArray &payload,
                                                QByteArray &reply)
{
    if (payload.isEmpty()) return false;
    
    auto replyBuffer = m_networkManager.post(request, payload);
    
    waitForResponse(replyBuffer);
    
    if (!replyBuffer->errorString().isEmpty() || replyBuffer->bytesAvailable() <= 0)
        return false;
    
    reply = replyBuffer->readAll();
    
    return true;
}

void NetworkRequestExecutor::waitForResponse(QNetworkReply *reply)
{
    QEventLoop eventLoop{};
    
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::exit);
    
    eventLoop.exec();
}
