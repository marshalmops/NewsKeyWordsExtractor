#include "SourcesFileManager.h"

bool SourcesFileManager::saveSources(const QString &filename)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Truncate))
        return false;
    
    decltype(auto) sources = SourceDictionary::getSources();
    QByteArray     sourcesBytes{};
    
    for (auto i = sources->begin(); i != sources->end(); ++i)
        sourcesBytes += (QByteArray::number((*i)->getType()) + (*i)->toByteArray() + C_SOURCES_SEPARATOR);
    
    if (file.write(sourcesBytes) != sourcesBytes.length()) return false;
    
    return true;
}

bool SourcesFileManager::loadSources(const QString &filename)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::ReadOnly))
        return false;
    
    QByteArray sourcesBytes{file.readAll()};
    
    if (sourcesBytes.length() < sizeof(AppContext::SourceType)) return false;
    
    QByteArray readBuffer{};
    size_t     curIndex  {0};
    
    while (true) {
        QByteArray rawSourceType{sourcesBytes.mid(curIndex, sizeof(AppContext::SourceType))};
        bool isConvOK{false};
        
        auto sourceType{static_cast<AppContext::SourceType>(rawSourceType.toUShort(&isConvOK))};
        
        if (!isConvOK) return false;
        
        curIndex += sizeof(AppContext::SourceType);
        
        while (true) {
            if (curIndex >= sourcesBytes.length()) return false;
            
            QChar readCharBuffer{sourcesBytes.at(curIndex)};
            
            if (readCharBuffer == C_SOURCES_SEPARATOR) {
                if (readBuffer.isEmpty()) return false;
               
                SourceDictionary::createNewSourceFromBytes(sourceType, readBuffer);
                
                readBuffer.clear();
                ++curIndex;
                
                break;
            }
            
            readBuffer += readCharBuffer;
            curIndex   += 1;
        }
        
        rawSourceType.clear();
    }
}

bool SourcesFileManager::saveSourcesContexts(const QString &filename)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Truncate))
        return false;
    
    decltype(auto) sourcesContexts = SourceDictionary::getSourcesContexts();
    QByteArray     sourcesContextsBytes{};
    
    for (auto i = sourcesContexts->begin(); i != sourcesContexts->end(); ++i)
        sourcesContextsBytes += (QByteArray::number((*i)->getType()) + (*i)->toByteArray() + C_SOURCES_SEPARATOR);
    
    if (file.write(sourcesContextsBytes) != sourcesContextsBytes.length()) return false;
    
    return true;
}

bool SourcesFileManager::loadSourcesContexts(const QString &filename)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::ReadOnly))
        return false;
    
    QByteArray sourcesContextsBytes{file.readAll()};
    
    if (sourcesContextsBytes.length() < sizeof(AppContext::SourceType)) return false;
    
    QByteArray readBuffer{};
    size_t     curIndex  {0};
    
    while (true) {
        if (curIndex >= sourcesContextsBytes.length()) break;
        
        QByteArray rawSourceType{sourcesContextsBytes.mid(curIndex, sizeof(AppContext::SourceType))};
        bool isConvOK{false};
        
        auto sourceType{static_cast<AppContext::SourceType>(rawSourceType.toUShort(&isConvOK))};
        
        if (!isConvOK) return false;
        
        curIndex += sizeof(AppContext::SourceType);
        
        while (true) {
            if (curIndex >= sourcesContextsBytes.length()) return false;
            
            QChar readCharBuffer{sourcesContextsBytes.at(curIndex)};
            
            if (readCharBuffer == C_SOURCES_SEPARATOR) {
                if (readBuffer.isEmpty())                                                    return false;
                if (!SourceDictionary::createSourceContextFromBytes(sourceType, readBuffer)) return false;
                
                readBuffer.clear();
                ++curIndex;
                
                break;
            }
            
            readBuffer += readCharBuffer;
            curIndex   += 1;
        }
        
        rawSourceType.clear();
    }
    
    return true;
}
