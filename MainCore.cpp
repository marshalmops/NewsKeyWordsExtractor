#include "MainCore.h"

MainCore::MainCore(std::shared_ptr<FileManager> fileManager, 
                   const uint16_t usedThreadsCount, 
                   QObject *parent)
    : QObject{parent},
      m_fileManager{fileManager},
      m_dictionary{std::make_shared<ThreadedStringDictionary<AppContext::WordsFrequency>>()},
      m_rawNewsQueue{std::make_shared<ThreadedQueue<RawNewsDataBase>>()},
      m_usedThreadsCount{usedThreadsCount},
      m_stopCounter{0},
      m_totalNewsCountOnProcessing{0},
      m_newsProcessedCounter{0}
{
    
}

void MainCore::launchWorkers(const uint16_t count)
{
                   
                   
    for (auto i = 0; i < count; ++i) {
        auto newWorker  = std::make_shared<MainCoreWorker>(m_dictionary, m_rawNewsQueue);
        auto *newThread = new QThread{};
        
        newWorker->moveToThread(newThread);
        m_coreWorkers.push_back(newWorker);
        
        connect(newThread, &QThread::started, newWorker.get(), &MainCoreWorker::start);
        
        connect(this, &MainCore::stop, newWorker.get(), &MainCoreWorker::stop, Qt::QueuedConnection);
        
        connect(newWorker.get(), &MainCoreWorker::stopped,           this, &MainCore::processStop,                           Qt::QueuedConnection);
        connect(newWorker.get(), &MainCoreWorker::errorOccured,      this, &MainCore::processError,                          Qt::QueuedConnection);
        connect(newWorker.get(), &MainCoreWorker::newsDataProcessed, this, &MainCore::checkReceivedDataProcessingCompleteon, Qt::QueuedConnection);
        
        newThread->start();
    }
}

void MainCore::processError(const Error err)
{
    QMessageBox{QMessageBox::Icon::Critical, tr("Error"), err.getText()}.exec();
    
    if (err.isCritical()) emit stop();
}

void MainCore::processReceivedData(std::vector<RawNewsDataBase> data)
{
    m_totalNewsCountOnProcessing = data.size();
    
    for (auto i = data.begin(); i != data.end(); ++i)
        m_rawNewsQueue->pushItem(std::move(*i));
}

void MainCore::checkReceivedDataProcessingCompleteon()
{
    ++m_newsProcessedCounter;
    
    if (m_newsProcessedCounter != m_totalNewsCountOnProcessing) return;
    
    if (!m_fileManager->saveJson(m_dictionary->toJson())) {
        processError(Error{tr("Dictionary saving error!"), true});
        
        return;
    }
    
    emit dataReceived();
}

void MainCore::addRSSSource(const QString rssUrl, 
                            const QString articleTextClass)
{
    if (!SourceDictionary::createNewSource(std::make_unique<SourceStandardRSS>(rssUrl, articleTextClass))) {
        processError(Error{tr("New RSS source creation error!"), true});
        
        return;
    }
    
    emit rssSourceAdded();
}

void MainCore::addTelegramSource(const QString telegramSource)
{
    if (!SourceDictionary::createNewSource(std::make_unique<SourceTelegram>(telegramSource))) {
        processError(Error{tr("New Telegram source creation error!"), true});
        
        return;
    }
    
    emit telegramSourceAdded();
}

void MainCore::deleteRSSSource(const AppContext::Id id)
{
    if (!SourceDictionary::deleteSourceById(id)) {
        processError(Error{tr("Chosen source deleting error!"), true});
        
        return;
    }
    
    emit rssSourceDeleted();
}

void MainCore::deleteTelegramSource(const AppContext::Id id)
{
    if (!SourceDictionary::deleteSourceById(id)) {
        processError(Error{tr("Chosen source deleting error!"), true});
        
        return;
    }
    
    emit telegramSourceDeleted();
}

void MainCore::setVKData(const AppContext::Token token)
{
    if (!SourceDictionary::createSourceContext(std::make_unique<SourceContextVK>(token))) {
        processError(Error{tr("VK context creation error!"), true});
        
        return;
    }
    
    if (!SourceDictionary::createNewSource(std::make_unique<SourceVK>())) {
        processError(Error{tr("VK source creation error!"), true});
        
        return;
    }
}

void MainCore::setTelegramData(const AppContext::Phone phone, 
                               const AppContext::Id apiId, 
                               const AppContext::Token apiHash)
{
    if (!SourceDictionary::createSourceContext(std::make_unique<SourceContextTelegram>(apiId, apiHash, phone))) {
        processError(Error{tr("Telegram context creation error!"), true});
        
        return;
    }
}

void MainCore::prepareGettingContext()
{
    emit networkContextPreparingRequested();
}

void MainCore::endGettingContextPreparing()
{
    emit networkContextPrepared();
}

void MainCore::getData()
{
    if (SourceDictionary::getSources()->empty()) {
        processError(Error{tr("No sources have been provided!")});
        
        emit dataNotReceived();
        
        return;
    }
    
    emit dataRequested();
}

void MainCore::processClose()
{
    emit stop();
}

void MainCore::processStop()
{
    ++m_stopCounter;
    
    if (m_stopCounter != m_usedThreadsCount) return;
    
    m_fileManager->getSourcesFileManager()->saveSources();
    m_fileManager->getSourcesFileManager()->saveSourcesContexts();
    
    QThread::currentThread()->quit();
}
