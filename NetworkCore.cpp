#include "NetworkCore.h"

NetworkCore::NetworkCore()
    : m_requestExecutor{std::make_shared<NetworkRequestExecutor>()},
      m_requestCreator{std::make_unique<NetworkRequestCreator>(std::make_unique<NetworkSourceContextPreparer>(m_requestExecutor))}
{
    
}

void NetworkCore::start()
{
    auto *dispatcher = QThread::currentThread()->eventDispatcher();
    
    while (true) {
        if (!dispatcher->processEvents(QEventLoop::ProcessEventsFlag::AllEvents))
            emit errorOccured(Error{"Event processing error!", true});
    }
}

void NetworkCore::stop()
{
    QThread::currentThread()->quit();
}

void NetworkCore::receiveData()
{
    auto sources = SourceDictionary::getSources();
    
    std::vector<RawNewsDataBase> data{};
    
    for (auto i = sources->begin(); i != sources->end(); ++i) {
        QNetworkRequest newRequest{};
        
        if (!m_requestCreator->createRequestForSource(&(*i), newRequest)) {
            emit errorOccured(Error{"Requests creating error!", true});
            
            return;
        }
        
        QByteArray newDataBytes{};
        
        if (!m_requestExecutor->executeGetRequest(newRequest, newDataBytes)) {
            emit errorOccured(Error{"Requests processing error!", true});
            
            return;
        }
        
        RawNewsDataBase newData{SourceDictionary::getSourceType(&(*i)), newDataBytes};
    
        data.push_back(newData);
    }
    
    emit dataReceived(data);
}
