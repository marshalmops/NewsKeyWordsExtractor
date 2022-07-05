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
    enum SourceType : uint8_t {
        ST_STANDARD_RSS = 0,
        ST_TELEGRAM,
        ST_VK
    };
    
    SourceDictionary() = delete;
    
    static bool createNewSourceFromBytes(const SourceType type,
                                         const QByteArray &data);
    static bool createSourceContextFromBytes(const SourceType type,
                                             const QByteArray &data);
    static bool createNewSource(std::unique_ptr<SourceBase> &source);
    
    template<class T>
    static SourceType getSourceType(T* source);
    template<class T>
    static SourceType getSourceContextType(T* source);
    
    static const std::shared_ptr<std::vector<SourceBase>>& getSources();
    static const std::shared_ptr<std::vector<std::shared_ptr<SourceContextInterface>>>& getSourcesContexts();
    
private:
    static std::shared_ptr<SourceContextInterface> getSourceContext(const SourceType sourceType);
    
private:
    static std::shared_ptr<std::vector<SourceBase>> m_sources;
    static std::shared_ptr<std::vector<std::shared_ptr<SourceContextInterface>>> m_sourcesContexts;
};

std::shared_ptr<std::vector<SourceBase>> SourceDictionary::m_sources = std::make_shared<std::vector<SourceBase>>();
std::shared_ptr<std::vector<std::shared_ptr<SourceContextInterface>>> SourceDictionary::m_sourcesContexts = std::make_shared<std::vector<std::shared_ptr<SourceContextInterface>>>();

#endif // SOURCEDICTIONARY_H
