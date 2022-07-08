#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include <QObject>
#include <QAbstractEventDispatcher>
#include <QThread>

#include "Error.h"

#include "SourceDictionary.h"

#include "NetworkRequestCreator.h"
#include "NetworkSourceContextPreparer.h"
#include "NetworkRequestExecutor.h"

#include "RawNewsDataBase.h"

#include "FormData.h"
#include "FormTemplate.h"

class NetworkCore : public QObject
{
    Q_OBJECT
public:
    NetworkCore();
    ~NetworkCore();
    
signals:
    // to MainCore:
    
    void errorOccured(const Error err);
    
    void contextPrepared();
    void dataReceived(std::vector<RawNewsDataBase> data);
    
    void additionalInputDataRequested(const FormTemplate paramsToGet);
    
    void stopped();
    
public slots:
    void start();
    void stop ();
    
    void prepareContext();
    void receiveData();
    
    void processGottenAdditionalInputData(const FormData gottenParams);
    
private:
    std::shared_ptr<NetworkRequestExecutor>       m_requestExecutor;
    std::shared_ptr<NetworkSourceContextPreparer> m_sourcePreparer;
    std::unique_ptr<NetworkRequestCreator>        m_requestCreator;
};

#endif // NETWORKCORE_H
