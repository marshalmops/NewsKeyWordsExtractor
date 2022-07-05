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
    NetworkRequestCreator(std::unique_ptr<NetworkSourceContextPreparer> &&sourcePreparer);
    
    template<class SourceType>
    bool createRequestForSource(SourceType *source, 
                                QNetworkRequest &request);
    
private:
    bool checkSourcePreparation(SourceBase *source);
    
private:
    std::unique_ptr<NetworkSourceContextPreparer> m_sourcePreparer;
};

#endif // NETWORKREQUESTCREATOR_H
