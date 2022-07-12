#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QJsonDocument>

#include "SourcesFileManager.h"

class FileManager : public QObject
{
public:
    constexpr static const char* C_DEFAULT_JSON_OUTPUT_FILENAME = "output.json";
    
    FileManager(const std::shared_ptr<SourcesFileManager> &sourcesFileManager);
    
    bool loadJson(const QString &filename,
                  QJsonDocument &jsonData);
    bool saveJson(const QJsonDocument &jsonData,
                  const QString &filename = C_DEFAULT_JSON_OUTPUT_FILENAME);
    
    std::shared_ptr<SourcesFileManager> getSourcesFileManager();
    
private:
    std::shared_ptr<SourcesFileManager> m_sourcesFileManager;
};

#endif // FILEMANAGER_H
