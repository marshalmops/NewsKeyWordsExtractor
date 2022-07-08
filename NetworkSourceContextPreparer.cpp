#include "NetworkSourceContextPreparer.h"

NetworkSourceContextPreparer::NetworkSourceContextPreparer(const std::shared_ptr<NetworkRequestExecutor> &networkExecutor)
    : m_networkExecutor{networkExecutor}
{
    
}

bool NetworkSourceContextPreparer::processGottenAdditionalInputData(const FormData &gottenParams)
{
    auto curPreparing = std::move(m_preparingBuffers.front());
    
    m_preparingBuffers.pop();
    
    return prepareSourceContext(curPreparing.m_contextPtr, gottenParams, curPreparing.m_curPreparingStep + 1);
}

bool NetworkSourceContextPreparer::isPreparationBufferEmpty() const
{
    return m_preparingBuffers.empty();
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
bool NetworkSourceContextPreparer::prepareSourceContext<SourceContextTelegram>(SourceContextTelegram *sourceContext,
                                                                               const FormData &preparingData,
                                                                               const uint8_t curStep)
{
    if (!sourceContext) return false;
    
    switch (curStep) {
    case 1: {
        NetworkSourceContextPreparer::ContextPreparingBuffer preparingBuffer{};
        
        preparingBuffer.m_type = SourceDictionary::SourceType::ST_TELEGRAM;
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

template<>
bool NetworkSourceContextPreparer::prepareSourceContext<SourceContextVK>(SourceContextVK *sourceContext,
                                                                         const FormData &preparingData,
                                                                         const uint8_t curStep)
{
    return true;
}

template<class SourceContextType>
bool NetworkSourceContextPreparer::prepareSourceContext(SourceContextType *sourceContext,
                                                        const FormData &preparingData,
                                                        const uint8_t curStep)
{
    return true;
}
