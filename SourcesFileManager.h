#ifndef SOURCESFILEMANAGER_H
#define SOURCESFILEMANAGER_H

#include <QString>
#include <QFile>

#include "SourceDictionary.h"

class SourcesFileManager
{
public:
    constexpr static const char* C_DEFAULT_SOURCES_FILENAME          = "sources.dat";
    constexpr static const char* C_DEFAULT_SOURCES_CONTEXTS_FILENAME = "sourcesContexts.dat";
    
    constexpr static const char C_SOURCES_SEPARATOR = '\n';
    
    SourcesFileManager() = default;
    
    bool saveSources(const QString &filename = QString{C_DEFAULT_SOURCES_FILENAME});
    bool loadSources(const QString &filename = QString{C_DEFAULT_SOURCES_FILENAME});
    
    bool saveSourcesContexts(const QString &filename = QString{C_DEFAULT_SOURCES_CONTEXTS_FILENAME});
    bool loadSourcesContexts(const QString &filename = QString{C_DEFAULT_SOURCES_CONTEXTS_FILENAME});
};

#endif // SOURCESFILEMANAGER_H
