#ifndef NETWORKREQUESTCREATOR_H
#define NETWORKREQUESTCREATOR_H

#include <QNetworkRequest>
#include <QUrlQuery>
#include <memory>

#include "SourceStandardRSS.h"
#include "SourceTelegram.h"
#include "SourceVK.h"

#include "SourceDictionary.h"

#include "NetworkSourceContextPreparer.h"

class NetworkRequestCreator
{
public:
    NetworkRequestCreator(const std::shared_ptr<NetworkSourceContextPreparer> &sourcePreparer);
    
    bool createRequestForRSSSource(SourceBase *source, 
                                   QNetworkRequest &request);
    bool createRequestForTelegramSource(SourceBase *source, 
                                        QNetworkRequest &request);
    bool createRequestForVKSource(SourceBase *source, 
                                  QNetworkRequest &request);
    bool createRequestForSource(SourceBase *source, 
                                QNetworkRequest &request);
    
    bool processAdditionalDataForPreparing(const std::vector<std::pair<QString, QString>> &gottenParams);
    
private:
    bool checkSourcePreparation(SourceBase *source);
    
private:
    std::shared_ptr<NetworkSourceContextPreparer> m_sourcePreparer;
};

#endif // NETWORKREQUESTCREATOR_H
