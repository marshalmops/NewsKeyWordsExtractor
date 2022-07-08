#include "AppInitializer.h"

bool AppInitializer::initializeApp(QApplication &app,
                                   AppView &appView, 
                                   std::unique_ptr<MainCore> &mainCore,
                                   std::unique_ptr<NetworkCore> &networkCore,
                                   std::shared_ptr<FileManager> &fileManager)
{
    fileManager = std::make_shared<FileManager>();
    
    if (!fileManager->getSourcesFileManager()->loadSourcesContexts()) {
        // no saved contexts or error occurance...
    } else {
        if (!fileManager->getSourcesFileManager()->loadSources()) {
            // no saved sources or error occurance...
        }
    }
    
    mainCore    = std::make_unique<MainCore>(fileManager, QThread::idealThreadCount() - 1);
    networkCore = std::make_unique<NetworkCore>();
    
    // signals / slots:
    
    // NetworkCore -> MainCore:
    
    QObject::connect(networkCore.get(), &NetworkCore::errorOccured, mainCore.get(),                 &MainCore::processError,                 Qt::QueuedConnection);
    QObject::connect(networkCore.get(), &NetworkCore::contextPrepared, mainCore.get(),              &MainCore::endGettingContextPreparing,   Qt::QueuedConnection);
    QObject::connect(networkCore.get(), &NetworkCore::dataReceived, mainCore.get(),                 &MainCore::processReceivedData,          Qt::QueuedConnection);
    QObject::connect(networkCore.get(), &NetworkCore::additionalInputDataRequested, mainCore.get(), &MainCore::additionalInputDataRequested, Qt::QueuedConnection);
    QObject::connect(networkCore.get(), &NetworkCore::stopped, mainCore.get(),                      &MainCore::processStop,                  Qt::QueuedConnection);
    
    // MainCore -> NetworkCore:
    
    QObject::connect(mainCore.get(), &MainCore::stop,                             networkCore.get(), &NetworkCore::stop,                             Qt::QueuedConnection);
    QObject::connect(mainCore.get(), &MainCore::dataRequested,                    networkCore.get(), &NetworkCore::receiveData,                      Qt::QueuedConnection);
    QObject::connect(mainCore.get(), &MainCore::additionalInputDataGot,           networkCore.get(), &NetworkCore::processGottenAdditionalInputData, Qt::QueuedConnection);
    QObject::connect(mainCore.get(), &MainCore::networkContextPreparingRequested, networkCore.get(), &NetworkCore::prepareContext,                   Qt::QueuedConnection);    
    
    // AppView -> MainCore:
    
    QObject::connect(&appView, &AppView::errorOccured,          mainCore.get(), &MainCore::processError);
    QObject::connect(&appView, &AppView::rssSourceAdded,        mainCore.get(), &MainCore::addRSSSource);
    QObject::connect(&appView, &AppView::telegramSourceAdded,   mainCore.get(), &MainCore::addTelegramSource);
    QObject::connect(&appView, &AppView::rssSourceDeleted,      mainCore.get(), &MainCore::deleteRSSSource);
    QObject::connect(&appView, &AppView::telegramSourceDeleted, mainCore.get(), &MainCore::deleteTelegramSource);
    QObject::connect(&appView, &AppView::vkDataProvided,        mainCore.get(), &MainCore::setVKData);
    QObject::connect(&appView, &AppView::telegramDataProvided,  mainCore.get(), &MainCore::setTelegramData);
    QObject::connect(&appView, &AppView::prepareContext,        mainCore.get(), &MainCore::prepareGettingContext);
    QObject::connect(&appView, &AppView::getData,               mainCore.get(), &MainCore::getData);
    QObject::connect(&appView, &AppView::formDataGot,           mainCore.get(), &MainCore::additionalInputDataGot);
    
    // MainCore -> AppView:
    
    QObject::connect(mainCore.get(), &MainCore::rssSourceAdded,               &appView, &AppView::insertRSSSourceRow);
    QObject::connect(mainCore.get(), &MainCore::telegramSourceAdded,          &appView, &AppView::insertTelegramSourceRow);
    QObject::connect(mainCore.get(), &MainCore::rssSourceDeleted,             &appView, &AppView::deleteRSSSourceRow);
    QObject::connect(mainCore.get(), &MainCore::telegramSourceDeleted,        &appView, &AppView::deleteTelegramSourceRow);
    QObject::connect(mainCore.get(), &MainCore::additionalInputDataRequested, &appView, &AppView::getFormDataByTemplate);
    QObject::connect(mainCore.get(), &MainCore::networkContextPrepared,       &appView, &AppView::endContextPreparing);
    
    //
    
    QObject::connect(&app, &QApplication::lastWindowClosed, mainCore.get(), &MainCore::processClose);
    
    
    return true;
}
