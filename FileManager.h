#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QJsonDocument>

#include "SourcesFileManager.h"

class FileManager
{
public:
    constexpr static const char* C_DEFAULT_JSON_OUTPUT_FILENAME = "output.json";
    
    FileManager(const std::shared_ptr<SourcesFileManager> &settingsManager);
    
    bool saveJson(const QJsonDocument &jsonData,
                  const QString &filename = C_DEFAULT_JSON_OUTPUT_FILENAME);
    
    std::shared_ptr<SourcesFileManager> getSettingsFileManager();
    
private:
    std::shared_ptr<SourcesFileManager> m_settingsManager;
};

#endif // FILEMANAGER_H
