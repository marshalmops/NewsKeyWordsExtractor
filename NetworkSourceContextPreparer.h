#ifndef NETWORKSOURCECONTEXTPREPARER_H
#define NETWORKSOURCECONTEXTPREPARER_H

#include "SourceContextTelegram.h"
#include "SourceContextVK.h"

#include "SourceTelegram.h"
#include "SourceVK.h"

#include "NetworkRequestExecutor.h"

class NetworkSourceContextPreparer : public QObject
{
public:
    NetworkSourceContextPreparer(const std::shared_ptr<NetworkRequestExecutor> &networkExecutor);
    
    template<class SourceType>
    bool prepareSource(SourceType *source);
    
    template<class SourceContextType>
    bool prepareSourceContext(SourceContextType *sourceContext);
    
private:
    std::shared_ptr<NetworkRequestExecutor> m_networkExecutor;
};

#endif // NETWORKSOURCECONTEXTPREPARER_H
