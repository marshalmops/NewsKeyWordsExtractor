#include "SourceDictionary.h"

std::shared_ptr<std::vector<std::shared_ptr<SourceBase>>> SourceDictionary::m_sources = std::make_shared<std::vector<std::shared_ptr<SourceBase>>>();
std::shared_ptr<std::vector<std::shared_ptr<SourceContextInterface>>> SourceDictionary::m_sourcesContexts = std::make_shared<std::vector<std::shared_ptr<SourceContextInterface>>>();

bool SourceDictionary::createNewSourceFromBytes(const AppContext::SourceType type, 
                                                const QByteArray &data)
{
    std::unique_ptr<SourceBase> source;
    
    switch (type) {
    case AppContext::SourceType::ST_STANDARD_RSS: {
        source = std::make_unique<SourceStandardRSS>();
        
        break;
    }
    case AppContext::SourceType::ST_TELEGRAM: {
        source = std::make_unique<SourceTelegram>();
        
        if (!source->setContext(getSourceContext(type))) return false;
        
        break;
    }
    case AppContext::SourceType::ST_VK: {
        if (getSourceIteratorByType(AppContext::SourceType::ST_VK) != m_sources->end())
            return true;
        
        source = std::make_unique<SourceVK>();
        
        if (!source->setContext(getSourceContext(type))) return false;
        
        break;
    }
    default: return false;
    }
    
    if (!source->fromByteArray(data)) return false;
    
    source->setId(m_sources->size() + 1);
    m_sources->push_back(std::shared_ptr<SourceBase>(source.release()));
    
    return true;
}

bool SourceDictionary::createSourceContextFromBytes(const AppContext::SourceType type,
                                                    const QByteArray &data)
{
    std::shared_ptr<SourceContextInterface> sourceContext;
    
    switch (type) {
    case AppContext::SourceType::ST_STANDARD_RSS: {return true;}
    case AppContext::SourceType::ST_TELEGRAM: {
        sourceContext = std::make_shared<SourceContextTelegram>();
        
        break;
    }
    case AppContext::SourceType::ST_VK: {
        sourceContext = std::make_shared<SourceContextVK>();
        
        if (type == AppContext::SourceType::ST_VK) {
            if (getSourceIteratorByType(AppContext::SourceType::ST_VK) == m_sources->end()) {
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
    
    auto sourceType = source->getType();
    
    switch (sourceType) {
    case AppContext::SourceType::ST_STANDARD_RSS: {break;}
    case AppContext::SourceType::ST_TELEGRAM: {
        if (!source->setContext(getSourceContext(sourceType))) return false;
        
        break;
    }
    case AppContext::SourceType::ST_VK: {
        if (getSourceIteratorByType(AppContext::SourceType::ST_VK) != m_sources->end())
            return true;
        
        if (!source->setContext(getSourceContext(sourceType))) return false;
        
        break;
    }
    default: return false;
    }
    
    source->setId(m_sources->size() + 1);
    m_sources->push_back(std::shared_ptr<SourceBase>(source.release()));
    
    return true;
}

bool SourceDictionary::createSourceContext(std::unique_ptr<SourceContextInterface> &&sourceContext)
{
    if (!sourceContext.get()) return false;
    
    auto sourceContextType = sourceContext->getType();
    auto prevSourceContext = getSourceContext(sourceContextType);
    
    if (!prevSourceContext.get()) {
        m_sourcesContexts->push_back(std::shared_ptr<SourceContextInterface>(sourceContext.release()));
    } else {
        switch (sourceContextType) {
        case AppContext::SourceType::ST_TELEGRAM: {
            auto telegramContext = dynamic_cast<SourceContextTelegram*>(prevSourceContext.get());
            auto newContext      = dynamic_cast<SourceContextTelegram*>(sourceContext.release());
            
            if (!telegramContext || !newContext) return false;
            
            *telegramContext = std::move(*newContext);
            
            break;
        }
        case AppContext::SourceType::ST_VK: {
            auto vkContext  = dynamic_cast<SourceContextVK*>(prevSourceContext.get());
            auto newContext = dynamic_cast<SourceContextVK*>(sourceContext.release());
            
            if (!vkContext || !newContext) return false;
            
            *vkContext = std::move(*newContext);
            
            break;
        }
        default: return false;
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

std::shared_ptr<SourceContextInterface> SourceDictionary::getSourceContext(const AppContext::SourceType sourceType)
{
    for (auto i = m_sourcesContexts->begin(); i != m_sourcesContexts->end(); ++i) {
        if ((*i)->getType() == sourceType)
            return *i;
    }
    
    return std::shared_ptr<SourceContextInterface>{nullptr};
}

std::vector<std::shared_ptr<SourceBase>>::iterator SourceDictionary::getSourceIteratorById(const AppContext::Id id)
{
    for (auto i = m_sources->begin(); i != m_sources->end(); ++i) {
        if ((*i)->getId() == id) return i;
    }
    
    return m_sources->end();
}

std::vector<std::shared_ptr<SourceBase>>::iterator SourceDictionary::getSourceIteratorByType(const AppContext::SourceType sourceType)
{
    for (auto i = m_sources->begin(); i != m_sources->end(); ++i) {
        if ((*i)->getType() == sourceType) return i;
    }
    
    return m_sources->end();
}
