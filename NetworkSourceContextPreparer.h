#ifndef NETWORKSOURCECONTEXTPREPARER_H
#define NETWORKSOURCECONTEXTPREPARER_H

#include <QObject>
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
    Q_OBJECT
    
    struct ContextPreparingBuffer {
        uint8_t m_preparingStepNumb;
        uint8_t m_curPreparingStep;
        
        SourceContextInterface *m_contextPtr;
    };
    
public:
    NetworkSourceContextPreparer(const std::shared_ptr<NetworkRequestExecutor> &networkExecutor);
    
    bool prepareRSSSource     (SourceStandardRSS *source);
    bool prepareTelegramSource(SourceTelegram *source);
    bool prepareVKSource      (SourceVK *source);
    bool prepareSource        (SourceBase *source);
    
    bool prepareTelegramSourceContext(SourceContextTelegram *sourceContext, 
                                      const FormData &preparingData = FormData{},
                                      const uint8_t curStep = 1);
    bool prepareVKSourceContext(SourceContextVK *sourceContext, 
                                const FormData &preparingData = FormData{},
                                const uint8_t curStep = 1);
    bool prepareSourceContext(SourceContextInterface *sourceContext, 
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
