#include "MainCoreWorker.h"

MainCoreWorker::MainCoreWorker(const std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency> > &dictionary, 
                               const std::shared_ptr<ThreadedQueue<RawNewsDataBase> > &rawNews, 
                               QObject *parent)
    : QObject{parent},
      m_dictionary{dictionary},
      m_rawNewsQueue{rawNews},
      m_textKeyWordsExtractor{std::make_unique<TextKeyWordsExtractor>()}
{
    
}

MainCoreWorker::~MainCoreWorker()
{
    //QThread::currentThread()->quit();
}

void MainCoreWorker::start()
{
    auto *dispatcher = QThread::currentThread()->eventDispatcher();
    
    while (true) {
        if (!dispatcher->processEvents(QEventLoop::ProcessEventsFlag::AllEvents)) {
            emit errorOccured(Error{"Event processing error!", true});
            
            continue;
        }
        
        RawNewsDataBase newRawNews{};
        
        if (!m_rawNewsQueue->takeItem(newRawNews)) continue;
        
        std::vector<News> parsedNews{};
        
        if (!ParserDictionary::parseData(newRawNews, parsedNews)) {
            emit errorOccured(Error{"Raw news parsing error!", true});
            
            continue;
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
    //this->~MainCoreWorker();
    QThread::currentThread()->quit();
    QThread::currentThread()->deleteLater();
            
    emit stopped();
}
