#ifndef NETWORKSOURCECONTEXTPREPARER_H
#define NETWORKSOURCECONTEXTPREPARER_H

#include <queue>

#include "SourceContextTelegram.h"
#include "SourceContextVK.h"

#include "SourceDictionary.h"

#include "SourceTelegram.h"
#include "SourceVK.h"

#include "NetworkRequestExecutor.h"

#include "FormData.h"
#include "FormTemplate.h"

class NetworkSourceContextPreparer : public QObject
{
    struct ContextPreparingBuffer {
        SourceDictionary::SourceType m_type;
        uint8_t                      m_preparingStepNumb;
        uint8_t                      m_curPreparingStep;
        
        SourceContextInterface *m_contextPtr;
    };
    
public:
    NetworkSourceContextPreparer(const std::shared_ptr<NetworkRequestExecutor> &networkExecutor);
    
    template<class SourceType>
    bool prepareSource(SourceType *source);
    
    template<class SourceContextType>
    bool prepareSourceContext(SourceContextType *sourceContext, 
                              const FormData &preparingData = FormData{},
                              const uint8_t curStep = 1);
    
    bool processGottenAdditionalInputData(const FormData &gottenParams);
    
    bool isPreparationBufferEmpty() const;
    
signals:
    void additionalInputDataRequested(const FormTemplate paramsToGet);
    
private:
    std::shared_ptr<NetworkRequestExecutor> m_networkExecutor;
    
    std::queue<ContextPreparingBuffer> m_preparingBuffers;
};

#endif // NETWORKSOURCECONTEXTPREPARER_H
