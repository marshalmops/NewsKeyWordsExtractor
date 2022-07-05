#include "SourcesFileManager.h"

bool SourcesFileManager::saveSources(const QString &filename)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Truncate))
        return false;
    
    decltype(auto) sources = SourceDictionary::getSources();
    QByteArray     sourcesBytes{};
    
    for (auto i = sources->begin(); i != sources->end(); ++i)
        sourcesBytes += (QByteArray::number(SourceDictionary::getSourceType(&(*i))) + i->toByteArray() + C_SOURCES_SEPARATOR);
    
    if (file.write(sourcesBytes) != sourcesBytes.length()) return false;
    
    return true;
}

bool SourcesFileManager::loadSources(const QString &filename)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::ReadOnly))
        return false;
    
    QByteArray sourcesBytes{file.readAll()};
    
    if (sourcesBytes.length() < sizeof(SourceDictionary::SourceType)) return false;
    
    QByteArray readBuffer{};
    size_t     curIndex  {0};
    
    while (true) {
        QByteArray rawSourceType{sourcesBytes.mid(curIndex, sizeof(SourceDictionary::SourceType))};
        bool isConvOK{false};
        
        auto sourceType{static_cast<SourceDictionary::SourceType>(rawSourceType.toUShort(&isConvOK))};
        
        if (!isConvOK) return false;
        
        curIndex += sizeof(SourceDictionary::SourceType);
        
        while (true) {
            if (curIndex >= sourcesBytes.length()) return false;
            
            QChar readCharBuffer{sourcesBytes.at(curIndex)};
            
            if (readCharBuffer == C_SOURCES_SEPARATOR) {
                if (readBuffer.isEmpty())                                                return false;
                if (!SourceDictionary::createNewSourceFromBytes(sourceType, readBuffer)) return false;
                
                readBuffer.clear();
                
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
        sourcesContextsBytes += (QByteArray::number(SourceDictionary::getSourceContextType(&(*i))) + (*i)->toByteArray() + C_SOURCES_SEPARATOR);
    
    if (file.write(sourcesContextsBytes) != sourcesContextsBytes.length()) return false;
    
    return true;
}

bool SourcesFileManager::loadSourcesContexts(const QString &filename)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::ReadOnly))
        return false;
    
    QByteArray sourcesContextsBytes{file.readAll()};
    
    if (sourcesContextsBytes.length() < sizeof(SourceDictionary::SourceType)) return false;
    
    QByteArray readBuffer{};
    size_t     curIndex  {0};
    
    while (true) {
        QByteArray rawSourceType{sourcesContextsBytes.mid(curIndex, sizeof(SourceDictionary::SourceType))};
        bool isConvOK{false};
        
        auto sourceType{static_cast<SourceDictionary::SourceType>(rawSourceType.toUShort(&isConvOK))};
        
        if (!isConvOK) return false;
        
        curIndex += sizeof(SourceDictionary::SourceType);
        
        while (true) {
            if (curIndex >= sourcesContextsBytes.length()) return false;
            
            QChar readCharBuffer{sourcesContextsBytes.at(curIndex)};
            
            if (readCharBuffer == C_SOURCES_SEPARATOR) {
                if (readBuffer.isEmpty())                                                    return false;
                if (!SourceDictionary::createSourceContextFromBytes(sourceType, readBuffer)) return false;
                
                readBuffer.clear();
                
                break;
            }
            
            readBuffer += readCharBuffer;
            curIndex   += 1;
        }
        
        rawSourceType.clear();
    }
}
