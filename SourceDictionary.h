#ifndef SOURCEDICTIONARY_H
#define SOURCEDICTIONARY_H

#include <stdint.h>
#include <QByteArray>
#include <vector>
#include <memory>

#include "SourceBase.h"

#include "SourceStandardRSS.h"
#include "SourceTelegram.h"
#include "SourceVK.h"

#include "SourceContextTelegram.h"
#include "SourceContextVK.h"

class SourceDictionary
{
public:
    SourceDictionary() = delete;
    
    static bool createNewSourceFromBytes(const AppContext::SourceType type,
                                         const QByteArray &data);
    static bool createSourceContextFromBytes(const AppContext::SourceType type,
                                             const QByteArray &data);
    static bool createNewSource(std::unique_ptr<SourceBase> &&source);
    static bool createSourceContext(std::unique_ptr<SourceContextInterface> &&sourceContext);
    
    static bool deleteSourceById(const AppContext::Id id);
    
    static const std::shared_ptr<std::vector<std::shared_ptr<SourceBase>>>& getSources();
    static const std::shared_ptr<std::vector<std::shared_ptr<SourceContextInterface>>>& getSourcesContexts();
    
private:
    static std::shared_ptr<SourceContextInterface> getSourceContext(const AppContext::SourceType sourceType);
    static std::vector<std::shared_ptr<SourceBase>>::iterator getSourceIteratorById(const AppContext::Id id);
    static std::vector<std::shared_ptr<SourceBase>>::iterator getSourceIteratorByType(const AppContext::SourceType sourceType);
    
private:
    static std::shared_ptr<std::vector<std::shared_ptr<SourceBase>>>             m_sources;
    static std::shared_ptr<std::vector<std::shared_ptr<SourceContextInterface>>> m_sourcesContexts;
};

#endif // SOURCEDICTIONARY_H
