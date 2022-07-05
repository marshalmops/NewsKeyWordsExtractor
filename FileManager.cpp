#include "FileManager.h"

FileManager::FileManager(const std::shared_ptr<SourcesFileManager> &settingsManager)
    : m_settingsManager{settingsManager}
{
    
}

bool FileManager::saveJson(const QJsonDocument &jsonData, 
                           const QString &filename)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::WriteOnly)) return false;
    
    QByteArray jsonBytes{jsonData.toJson()};
    
    return file.write(jsonBytes) == jsonBytes.length();
}

std::shared_ptr<SourcesFileManager> FileManager::getSettingsFileManager()
{
    return m_settingsManager;
}
