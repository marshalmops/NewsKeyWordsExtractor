#ifndef MAINCORE_H
#define MAINCORE_H

#include <QObject>
#include <QMessageBox>

#include "FileManager.h"

#include "MainCoreWorker.h"

#include "ThreadedStringDictionary.h"
#include "ThreadedQueue.h"

#include "SourceDictionary.h"

#include "FormData.h"
#include "FormTemplate.h"
 
class MainCore : public QObject
{
    Q_OBJECT
public:
    explicit MainCore(std::shared_ptr<FileManager> fileManager,
                      const uint16_t usedThreadsCount,
                      QObject *parent = nullptr);
    
signals:
    // to MainCoreWorker & NetworkCore:
    
    void stop();
    
    // to NetworkCore:
    
    void dataRequested();
    
    // to AppView:
    
    void dataReceived();
    void dataNotReceived();
    
    void rssSourceAdded     ();
    void telegramSourceAdded();
    
    void rssSourceDeleted     ();
    void telegramSourceDeleted();
    
    // routing signals for NetworkCore & AppView:
    
    void additionalInputDataRequested(const FormTemplate paramsToGet);
    void additionalInputDataGot      (const FormData gottenData);
    
    // ;
    
    void networkContextPreparingRequested(); // to NetworkCore
    void networkContextPrepared          (); // to AppView
    
public slots:
    void launchWorkers(const uint16_t count);
    
    void processError(const Error err);
    
    void getData();
    void processReceivedData(std::vector<RawNewsDataBase> data);
    void checkReceivedDataProcessingCompleteon();
    
    void addRSSSource     (const QString rssUrl,
                           const QString articleTextClass);
    void addTelegramSource(const QString telegramSource);
    
    void deleteRSSSource     (const AppContext::Id id);
    void deleteTelegramSource(const AppContext::Id id);
    
    void setVKData      (const AppContext::Token token);
    void setTelegramData(const AppContext::Phone phone,
                         const AppContext::Id apiId,
                         const AppContext::Token apiHash);
    
    void prepareGettingContext();
    void endGettingContextPreparing();
    
    void processClose();
    
    void processStop();
    
private:
    std::shared_ptr<FileManager> m_fileManager;
    
    std::vector<std::shared_ptr<MainCoreWorker>> m_coreWorkers;
    
    std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency>> m_dictionary;
    std::shared_ptr<ThreadedQueue<RawNewsDataBase>> m_rawNewsQueue;
    
    uint16_t m_usedThreadsCount;
    uint16_t m_stopCounter;
    
    uint64_t m_totalNewsCountOnProcessing;
    uint64_t m_newsProcessedCounter;
};

#endif // MAINCORE_H
