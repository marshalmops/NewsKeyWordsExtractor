#include "FileManager.h"

FileManager::FileManager(const std::shared_ptr<SourcesFileManager> &sourcesFileManager)
    : m_sourcesFileManager{sourcesFileManager}
{
    
}

bool FileManager::loadJson(const QString &filename, 
                           QJsonDocument &jsonData)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::ReadOnly)) return false;
    
    QByteArray jsonBytes{file.readAll()};
    
    if (jsonBytes.isEmpty()) return false;
    
    jsonData = QJsonDocument::fromJson(jsonBytes);
    
    return !jsonData.isEmpty();
}

bool FileManager::saveJson(const QJsonDocument &jsonData, 
                           const QString &filename)
{
    QFile file{filename};
    
    if (!file.open(QFile::OpenModeFlag::WriteOnly)) return false;
    
    QByteArray jsonBytes{jsonData.toJson()};
    
    return file.write(jsonBytes) == jsonBytes.length();
}

std::shared_ptr<SourcesFileManager> FileManager::getSourcesFileManager()
{
    return m_sourcesFileManager;
}
