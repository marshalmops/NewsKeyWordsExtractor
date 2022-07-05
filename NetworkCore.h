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

class NetworkCore : public QObject
{
    Q_OBJECT
public:
    NetworkCore();
    
signals:
    void errorOccured(const Error err);
    
    void dataReceived(std::vector<RawNewsDataBase> data);
    
public slots:
    void start();
    void stop ();
    
    void receiveData();
    
private:
    std::shared_ptr<NetworkRequestExecutor> m_requestExecutor;
    std::unique_ptr<NetworkRequestCreator>  m_requestCreator;
};

#endif // NETWORKCORE_H
