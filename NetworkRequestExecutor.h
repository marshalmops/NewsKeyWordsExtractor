#ifndef NETWORKREQUESTEXECUTOR_H
#define NETWORKREQUESTEXECUTOR_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QAbstractEventDispatcher>
#include <QEventLoop>

class NetworkRequestExecutor
{
public:
    NetworkRequestExecutor(QObject *networkManagerParent = nullptr);
    
    bool executeGetRequest(const QNetworkRequest &request,
                           QByteArray &reply);
    bool executePostRequest(const QNetworkRequest &request,
                            const QByteArray &payload,
                            QByteArray &reply);
    
private:
    void waitForResponse(QNetworkReply *reply);
    
private:
    QNetworkAccessManager m_networkManager;
};

#endif // NETWORKREQUESTEXECUTOR_H
