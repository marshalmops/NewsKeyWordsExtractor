#include "NetworkSourceContextPreparer.h"

NetworkSourceContextPreparer::NetworkSourceContextPreparer(const std::shared_ptr<NetworkRequestExecutor> &networkExecutor)
    : m_networkExecutor{networkExecutor}
{
    
}


template<>
bool NetworkSourceContextPreparer::prepareSource<SourceTelegram>(SourceTelegram *source)
{
    if (!source) return false;
    if (source->isPrepared()) return true;
    
    auto context = source->getContext(); 
    auto telegramContext = dynamic_cast<SourceContextTelegram*>(context.get()); // FIXME: not clear
    
    if (!telegramContext->isPrepared()) return false;
    
    // resolving channel name to channelId...
    
    // recreation of SourceTelegram obj. with gotten channelId value...
    
    return true;
}

template<class SourceType>
bool NetworkSourceContextPreparer::prepareSource(SourceType *source)
{
    return true;
}

template<>
bool NetworkSourceContextPreparer::prepareSourceContext<SourceContextTelegram>(SourceContextTelegram *sourceContext)
{
    if (!sourceContext) return false;
    
    // auth processing...

    return true;
}

template<>
bool NetworkSourceContextPreparer::prepareSourceContext<SourceContextVK>(SourceContextVK *sourceContext)
{
    return true;
}

template<class SourceContextType>
bool NetworkSourceContextPreparer::prepareSourceContext(SourceContextType *sourceContext)
{
    return true;
}
