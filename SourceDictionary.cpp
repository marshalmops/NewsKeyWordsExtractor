#include "SourceDictionary.h"

bool SourceDictionary::createNewSourceFromBytes(const SourceType type, 
                                                const QByteArray &data)
{
    std::unique_ptr<SourceBase> source;
    
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
        if (getSourceIteratorByType(SourceType::ST_VK) != m_sources->end())
            return true;
        
        source = std::make_unique<SourceVK>();
        
        if (!source->setContext(getSourceContext(type))) return false;
        
        break;
    }
    default: return false;
    }
    
    if (!source->fromByteArray(data)) return false;
    
    source->setId(m_sources->size());
    m_sources->push_back(std::shared_ptr<SourceBase>(source.release()));
    
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
        
        if (type == SourceType::ST_VK) {
            if (getSourceIteratorByType(SourceType::ST_VK) == m_sources->end()) {
                if (!createNewSource(std::make_unique<SourceVK>()))
                    return false;
            }
        }
        
        break;
    }
    default: return false;
    }
    
    if (!sourceContext->fromByteArray(data)) return false;
    
    m_sourcesContexts->push_back(sourceContext);
    
    return true;
}

bool SourceDictionary::createNewSource(std::unique_ptr<SourceBase> &&source)
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
        if (getSourceIteratorByType(SourceType::ST_VK) != m_sources->end())
            return true;
        
        if (!source->setContext(getSourceContext(sourceType))) return false;
        
        break;
    }
    default: return false;
    }
    
    source->setId(m_sources->size());
    m_sources->push_back(std::shared_ptr<SourceBase>(source.release()));
    
    return true;
}

bool SourceDictionary::createSourceContext(std::unique_ptr<SourceContextInterface> &&sourceContext)
{
    if (!sourceContext.get()) return false;
    
    auto sourceContextType = getSourceContextType(sourceContext.get());
    auto prevSourceContext = getSourceContext(sourceContextType);
    
    if (!prevSourceContext.get()) {
        m_sourcesContexts->push_back(std::shared_ptr<SourceContextInterface>(sourceContext.release()));
    } else
        *(prevSourceContext.get()) = *(sourceContext.release());
    
    if (sourceContextType == SourceType::ST_VK) {
        if (getSourceIteratorByType(SourceType::ST_VK) == m_sources->end()) {
            if (!createNewSource(std::make_unique<SourceVK>()))
                return false;
        }
    }
    
    return true;
}

bool SourceDictionary::deleteSourceById(const AppContext::Id id)
{
    if (id <= 0) return false;
    
    auto itemToDeleteIter = getSourceIteratorById(id);
    
    if (itemToDeleteIter == m_sources->end()) return false;
    
    m_sources->erase(itemToDeleteIter);
    
    return true;
}

const std::shared_ptr<std::vector<std::shared_ptr<SourceBase>>> &SourceDictionary::getSources()
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

std::vector<std::shared_ptr<SourceBase>>::iterator SourceDictionary::getSourceIteratorById(const AppContext::Id id)
{
    auto curIndex{0};
    
    for (auto i = m_sources->begin(); i != m_sources->end(); ++i) {
        if (curIndex == id) return i;
        
        ++curIndex;
    }
    
    return m_sources->end();
}

std::vector<std::shared_ptr<SourceBase>>::iterator SourceDictionary::getSourceIteratorByType(const SourceType sourceType)
{
    for (auto i = m_sources->begin(); i != m_sources->end(); ++i) {
        if (getSourceType(&(*i)) == sourceType) return i;
    }
    
    return m_sources->end();
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
