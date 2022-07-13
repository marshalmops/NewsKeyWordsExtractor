#include "MainCoreWorker.h"

MainCoreWorker::MainCoreWorker(const std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency> > &dictionary, 
                               const std::shared_ptr<ThreadedQueue<RawNewsDataBase> > &rawNews, 
                               QObject *parent)
    : QObject{parent},
      m_dictionary{dictionary},
      m_rawNewsQueue{rawNews},
      m_textKeyWordsExtractor{std::make_unique<TextKeyWordsExtractor>()},
      m_execThread{nullptr},
      m_isRunning{false}
{
    
}
MainCoreWorker::~MainCoreWorker()
{
    //QThread::currentThread()->quit();
}

void MainCoreWorker::start()
{
    auto *dispatcher = QThread::currentThread()->eventDispatcher();
    
    m_execThread.reset(QThread::currentThread());
    m_isRunning = true;
    
    while (m_isRunning) {
        dispatcher->processEvents(QEventLoop::ProcessEventsFlag::AllEvents);
        
#ifndef QT_DEBUG
        QThread::currentThread()->wait(AppContext::C_TICK_DELAY_MS);
#endif
        RawNewsDataBase newRawNews{};
        
        if (!m_rawNewsQueue->takeItem(newRawNews)) continue;
        
        News parsedNews{};
        
        switch (ParserDictionary::parseData(newRawNews, parsedNews)) {
        case NewsParserBase::ParsingResult::PR_ERROR: {
            emit errorOccured(Error{"Raw news parsing error!", true});
            
            continue;
        }
        case NewsParserBase::ParsingResult::PR_NO_DATA: {
            emit newsDataProcessed();
            
            continue;
        }
        }
        
        if (!m_textKeyWordsExtractor->extractKeyWordsOfNews(parsedNews, m_dictionary)) {
            emit errorOccured(Error{"Key words extracting error!", true});
            
            continue;
        }
        
        emit newsDataProcessed();
    }
}

void MainCoreWorker::stop()
{
    m_isRunning = false;
            
    emit stopped();
    
    QThread::currentThread()->quit();
}
