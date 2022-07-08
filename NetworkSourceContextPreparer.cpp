#include "NetworkSourceContextPreparer.h"

NetworkSourceContextPreparer::NetworkSourceContextPreparer(const std::shared_ptr<NetworkRequestExecutor> &networkExecutor)
    : QObject{},
      m_networkExecutor{networkExecutor}
{
    
}

bool NetworkSourceContextPreparer::prepareSource(SourceBase *source)
{
    if (!source) return false;
    if (source->isPrepared()) return true;

    switch (source->getType()) {
    case AppContext::SourceType::ST_STANDARD_RSS: return prepareRSSSource(dynamic_cast<SourceStandardRSS*>(source));
    case AppContext::SourceType::ST_TELEGRAM:     return prepareTelegramSource(dynamic_cast<SourceTelegram*>(source));
    case AppContext::SourceType::ST_VK:           return prepareVKSource(dynamic_cast<SourceVK*>(source));        
    }
    
    return false;
}

bool NetworkSourceContextPreparer::prepareRSSSource(SourceStandardRSS *source)
{
    return true;
}

bool NetworkSourceContextPreparer::prepareTelegramSource(SourceTelegram *source)
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

bool NetworkSourceContextPreparer::prepareVKSource(SourceVK *source)
{
    return true;
}

bool NetworkSourceContextPreparer::prepareTelegramSourceContext(SourceContextTelegram *sourceContext, 
                                                        const FormData &preparingData,
                                                        const uint8_t curStep)
{
    if (!sourceContext) return false;
    
    switch (curStep) {
    case 1: {
        NetworkSourceContextPreparer::ContextPreparingBuffer preparingBuffer{};
        
        preparingBuffer.m_preparingStepNumb = 2;
        preparingBuffer.m_curPreparingStep = 1;
        preparingBuffer.m_contextPtr = sourceContext;
        
        m_preparingBuffers.push(preparingBuffer);
        
        FormTemplate neededParams{};
        
        neededParams.addParam("Code", QMetaType::QString);
        
        emit additionalInputDataRequested(neededParams);
        
        break;
    }
    case 2: {
        // calling signIn using received CODE...
        
        break;
    }
    }

    return true;
}

bool NetworkSourceContextPreparer::prepareSourceContext(SourceContextInterface *sourceContext, 
                                                        const FormData &preparingData, 
                                                        const uint8_t curStep)
{
    if (!sourceContext) return false;
    if (sourceContext->isPrepared()) return true;

    switch (sourceContext->getType()) {
    case AppContext::SourceType::ST_TELEGRAM: return prepareTelegramSourceContext(dynamic_cast<SourceContextTelegram*>(sourceContext));
    case AppContext::SourceType::ST_VK:       return prepareVKSourceContext(dynamic_cast<SourceContextVK*>(sourceContext));        
    }
    
    return false;
}

bool NetworkSourceContextPreparer::prepareVKSourceContext(SourceContextVK *sourceContext,
                                                          const FormData &preparingData, 
                                                          const uint8_t curStep)
{
    return true;
}

bool NetworkSourceContextPreparer::processGottenAdditionalInputData(const FormData &gottenParams)
{
    auto curPreparing = std::move(m_preparingBuffers.front());
    
    m_preparingBuffers.pop();
    
    switch (curPreparing.m_contextPtr->getType()) {
    case AppContext::SourceType::ST_TELEGRAM: return prepareSourceContext(dynamic_cast<SourceContextTelegram*>(curPreparing.m_contextPtr), gottenParams, curPreparing.m_curPreparingStep + 1);
    case AppContext::SourceType::ST_VK:       return prepareSourceContext(dynamic_cast<SourceContextVK*>(curPreparing.m_contextPtr), gottenParams, curPreparing.m_curPreparingStep + 1);
    }
    
    return true;
}

bool NetworkSourceContextPreparer::isPreparationBufferEmpty() const
{
    return m_preparingBuffers.empty();
}
