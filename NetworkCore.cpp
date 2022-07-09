#include "NetworkCore.h"

NetworkCore::NetworkCore()
    : m_requestExecutor{std::make_shared<NetworkRequestExecutor>(this)},
      m_sourcePreparer{std::make_shared<NetworkSourceContextPreparer>(m_requestExecutor)},
      m_requestCreator{std::make_unique<NetworkRequestCreator>(m_sourcePreparer)},
      m_execThread{nullptr},
      m_isRunning{false}
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
    
    m_execThread.reset(QThread::currentThread());
    m_isRunning = true;
    
    while (m_isRunning) {
        dispatcher->processEvents(QEventLoop::ProcessEventsFlag::AllEvents);
    }
}

void NetworkCore::stop()
{
    //this->~NetworkCore();
    
    QThread::currentThread()->quit();
    
    m_isRunning = false;
    
    emit stopped();
}

void NetworkCore::prepareContext()
{
    auto contexts = SourceDictionary::getSourcesContexts();
    
    for (auto i = contexts->begin(); i != contexts->end(); ++i) {
        if (!m_sourcePreparer->prepareSourceContext((*i).get())) {
            emit errorOccured(Error{tr("Source context preparing error!"), true});
            
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
            emit errorOccured(Error{tr("Source preparing error!"), true});
            
            return;
        }
        
        QNetworkRequest newRequest{};
        
        if (!m_requestCreator->createRequestForSource((*i).get(), newRequest)) {
            emit errorOccured(Error{tr("Requests creating error!"), true});
            
            return;
        }
        
        QByteArray newDataBytes{};
        
        if (!m_requestExecutor->executeGetRequest(newRequest, newDataBytes)) {
            emit errorOccured(Error{tr("Requests processing error!"), true});
            
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
        emit errorOccured(Error{tr("Additional data processing error!"), true});
        
        return;
    }
    
    if (m_sourcePreparer->isPreparationBufferEmpty()) emit contextPrepared();
}
