#ifndef MAINCOREWORKER_H
#define MAINCOREWORKER_H

#include <QObject>
#include <QThread>
#include <QAbstractEventDispatcher>

#include "AppContext.h"
#include "Error.h"

#include "ThreadedStringDictionary.h"
#include "ThreadedQueue.h"

#include "RawNewsDataBase.h"

#include "ParserDictionary.h"

#include "TextKeyWordsExtractor.h"

class MainCoreWorker : public QObject
{
    Q_OBJECT
public:
    explicit MainCoreWorker(const std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency>> &dictionary,
                            const std::shared_ptr<ThreadedQueue<RawNewsDataBase>> &rawNews,
                            QObject *parent = nullptr);
    ~MainCoreWorker();
    
signals:
    void errorOccured(const Error err);
    
    void newsDataProcessed();
    
    void stopped();
    
public slots:
    void start();
    void stop();
    
private:
    std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency>> m_dictionary;
    std::shared_ptr<ThreadedQueue<RawNewsDataBase>> m_rawNewsQueue;
    
    std::unique_ptr<TextKeyWordsExtractor> m_textKeyWordsExtractor;
    
    std::unique_ptr<QThread> m_execThread;
    bool m_isRunning;
};

#endif // MAINCOREWORKER_H
