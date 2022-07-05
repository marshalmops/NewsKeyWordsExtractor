#include "SourceDictionary.h"

bool SourceDictionary::createNewSourceFromBytes(const SourceType type, 
                                                const QByteArray &data)
{
    std::unique_ptr<SourceBase> source;
    
    // FIXME: some defence related to multiple VK sources instanciation...
    
    switch (type) {
    case SourceType::ST_STANDARD_RSS: {
        source = std::make_unique<SourceStandardRSS>();
        
        break;
    }
    case SourceType::ST_TELEGRAM: {
        source = std::make_unique<SourceTelegram>();
        
        if (!source->setContext(getSourceContext(type))) return false;
        
        break;
    }
    case SourceType::ST_VK: {
        source = std::make_unique<SourceVK>();
        
        if (!source->setContext(getSourceContext(type))) return false;
        
        break;
    }
    }
    
    if (!source->fromByteArray(data)) return false;
    
    m_sources->push_back(std::move(*source.release()));
    
    return true;
}

bool SourceDictionary::createSourceContextFromBytes(const SourceType type,
                                                    const QByteArray &data)
{
    std::shared_ptr<SourceContextInterface> sourceContext;
    
    switch (type) {
    case SourceType::ST_STANDARD_RSS: {return true;}
    case SourceType::ST_TELEGRAM: {
        sourceContext = std::make_shared<SourceContextTelegram>();
        
        break;
    }
    case SourceType::ST_VK: {
        sourceContext = std::make_shared<SourceContextVK>();
        
        break;
    }
    }
    
    if (!sourceContext->fromByteArray(data)) return false;
    
    m_sourcesContexts->push_back(sourceContext);
    
    return true;
}

bool SourceDictionary::createNewSource(std::unique_ptr<SourceBase> &source)
{
    if (!source.get()) return false;
    
    auto sourceType = getSourceType(source.get());
    
    switch (sourceType) {
    case SourceType::ST_STANDARD_RSS: {break;}
    case SourceType::ST_TELEGRAM: {
        if (!source->setContext(getSourceContext(sourceType))) return false;
        
        break;
    }
    case SourceType::ST_VK: {
        // uniqueness checking...
        
        if (!source->setContext(getSourceContext(sourceType))) return false;
        
        break;
    }
    }
    
    m_sources->push_back(std::move(*source));
    
    return true;
}

const std::shared_ptr<std::vector<SourceBase>> &SourceDictionary::getSources()
{
    return m_sources;
}

const std::shared_ptr<std::vector<std::shared_ptr<SourceContextInterface>>> &SourceDictionary::getSourcesContexts()
{
    return m_sourcesContexts;
}

std::shared_ptr<SourceContextInterface> SourceDictionary::getSourceContext(const SourceType sourceType)
{
    for (auto i = m_sourcesContexts->begin(); i != m_sourcesContexts->end(); ++i) {
        if (getSourceContextType((*i).get()) == sourceType)
            return *i;
    }
    
    return std::shared_ptr<SourceContextInterface>{nullptr};
}

template<>
SourceDictionary::SourceType SourceDictionary::getSourceType<SourceStandardRSS>(SourceStandardRSS *source)
{
    return SourceType::ST_STANDARD_RSS;
}

template<>
SourceDictionary::SourceType SourceDictionary::getSourceType<SourceTelegram>(SourceTelegram *source)
{
    return SourceType::ST_TELEGRAM;
}

template<>
SourceDictionary::SourceType SourceDictionary::getSourceType<SourceVK>(SourceVK *source)
{
    return SourceType::ST_VK;
}

template<>
SourceDictionary::SourceType SourceDictionary::getSourceContextType<SourceContextTelegram>(SourceContextTelegram *source)
{
    return SourceType::ST_TELEGRAM;
}

template<>
SourceDictionary::SourceType SourceDictionary::getSourceContextType<SourceContextVK>(SourceContextVK *source)
{
    return SourceType::ST_VK;
}
