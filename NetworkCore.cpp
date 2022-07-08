#include "NetworkCore.h"

NetworkCore::NetworkCore()
    : m_requestExecutor{std::make_shared<NetworkRequestExecutor>()},
      m_sourcePreparer{std::make_shared<NetworkSourceContextPreparer>(m_requestExecutor)},
      m_requestCreator{std::make_unique<NetworkRequestCreator>(m_sourcePreparer)}
{
    QObject::connect(m_sourcePreparer.get(), &NetworkSourceContextPreparer::additionalInputDataRequested, this, &NetworkCore::additionalInputDataRequested);
}

NetworkCore::~NetworkCore()
{
    //QThread::currentThread()->quit();
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
    //this->~NetworkCore();
    
    QThread::currentThread()->quit();
    QThread::currentThread()->deleteLater();
    
    emit stopped();
}

void NetworkCore::prepareContext()
{
    auto contexts = SourceDictionary::getSourcesContexts();
    
    for (auto i = contexts->begin(); i != contexts->end(); ++i) {
        if (!m_sourcePreparer->prepareSourceContext((*i).get())) {
            emit errorOccured(Error{"Source context preparing error!", true});
            
            return;
        }
    }
    
    if (m_sourcePreparer->isPreparationBufferEmpty()) emit contextPrepared();
}

void NetworkCore::receiveData()
{
    auto sources = SourceDictionary::getSources();
    
    std::vector<RawNewsDataBase> data{};
    
    for (auto i = sources->begin(); i != sources->end(); ++i) {
        if (!m_sourcePreparer->prepareSource((*i).get())) {
            emit errorOccured(Error{"Source preparing error!", true});
            
            return;
        }
        
        QNetworkRequest newRequest{};
        
        if (!m_requestCreator->createRequestForSource((*i).get(), newRequest)) {
            emit errorOccured(Error{"Requests creating error!", true});
            
            return;
        }
        
        QByteArray newDataBytes{};
        
        if (!m_requestExecutor->executeGetRequest(newRequest, newDataBytes)) {
            emit errorOccured(Error{"Requests processing error!", true});
            
            return;
        }
        
        RawNewsDataBase newData{(*i)->getType(), newDataBytes};
    
        data.push_back(newData);
    }
    
    emit dataReceived(data);
}

void NetworkCore::processGottenAdditionalInputData(const FormData gottenParams)
{
    if (!m_sourcePreparer->processGottenAdditionalInputData(gottenParams)) {
        emit errorOccured(Error{"Additional data processing error!", true});
        
        return;
    }
    
    if (m_sourcePreparer->isPreparationBufferEmpty()) emit contextPrepared();
}
