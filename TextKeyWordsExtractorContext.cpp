#include "TextKeyWordsExtractorContext.h"

std::shared_ptr<QStringList> TextKeyWordsExtractorContext::m_bannedWordsList = std::make_shared<QStringList>();
float TextKeyWordsExtractorContext::m_equalityCoef = C_DEFAULT_EQUALITY_COEF;

bool TextKeyWordsExtractorContext::initializeContext(const std::shared_ptr<FileManager> &fileManager)
{
    if (!fileManager.get()) return false;
    
    QJsonDocument keyWordsExtractorConfigJson{};
    
    if (!fileManager->loadJson(C_KEY_WORDS_EXTRACTOR_CONFIG_FILENAME, keyWordsExtractorConfigJson))  {
        keyWordsExtractorConfigJson.setObject(generateConfigFileJson());
        
        fileManager->saveJson(keyWordsExtractorConfigJson, C_KEY_WORDS_EXTRACTOR_CONFIG_FILENAME);
        
        return false;
    }
    
    auto rootObject = keyWordsExtractorConfigJson.object();
    
    if (rootObject.isEmpty()) return false;
    
    loadBannedWords(rootObject);
    
    if (!rootObject.contains(C_EQUALITY_COEF_PROP_NAME))   return false;
    if (!rootObject[C_EQUALITY_COEF_PROP_NAME].isDouble()) return false;
    
    auto equalityCoefRaw = rootObject[C_EQUALITY_COEF_PROP_NAME].toDouble();
    
    if (equalityCoefRaw < 0) return false;
    
    m_equalityCoef = equalityCoefRaw;
    
    return true;
}

const std::shared_ptr<QStringList> &TextKeyWordsExtractorContext::getBannedWordsList()
{
    return m_bannedWordsList;
}

float TextKeyWordsExtractorContext::getEqualityCoef()
{
    return m_equalityCoef;
}

bool TextKeyWordsExtractorContext::loadBannedWords(const QJsonObject &root)
{
    if (!root.contains(C_BANNED_WORDS_PROP_NAME))  return false;
    if (!root[C_BANNED_WORDS_PROP_NAME].isArray()) return false;
    
    auto bannedWordsArray = root[C_BANNED_WORDS_PROP_NAME].toArray();
    
    foreach (const auto &bannedWord, bannedWordsArray) {
        QString bannedWordString{};
        
        if (!bannedWord.isString()) return false;
        
        bannedWordString = bannedWord.toString();
        
        if (bannedWordString.isEmpty()) return false;
        
        m_bannedWordsList->push_back(std::move(bannedWordString));
    }
    
    return true;
}

QJsonObject TextKeyWordsExtractorContext::generateConfigFileJson()
{
    QJsonObject newConfigFileRoot{};
    
    newConfigFileRoot.insert(C_BANNED_WORDS_PROP_NAME, QJsonArray{});
    newConfigFileRoot.insert(C_EQUALITY_COEF_PROP_NAME, C_DEFAULT_EQUALITY_COEF);
    
    return newConfigFileRoot;
}
