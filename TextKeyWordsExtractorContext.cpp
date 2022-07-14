#include "TextKeyWordsExtractorContext.h"

std::shared_ptr<QStringList> TextKeyWordsExtractorContext::m_bannedWordsList = std::make_shared<QStringList>();
float TextKeyWordsExtractorContext::m_equalityCoef = C_DEFAULT_EQUALITY_COEF;
uint16_t TextKeyWordsExtractorContext::m_maxKeyWordsCount = C_DEFAULT_MAX_KEY_WORDS_COUNT;

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
    
    QVariant curValue{};
    
    if (loadIntegralPropValue(rootObject, C_EQUALITY_COEF_PROP_NAME, curValue)) {
        if (curValue.toDouble() < 0) {
            return false;
            
        } else {
            m_equalityCoef = curValue.toDouble();
        }
    }
    
    if (loadIntegralPropValue(rootObject, C_MAX_KEY_WORDS_COUNT_PROP_NAME, curValue)) {
        m_equalityCoef = curValue.toUInt();
    }
    
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

uint32_t TextKeyWordsExtractorContext::getMaxKeyWordsCount()
{
    return m_maxKeyWordsCount;
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

bool TextKeyWordsExtractorContext::loadIntegralPropValue(const QJsonObject &root,
                                                         const char *propName,
                                                         QVariant &propValue)
{
    if (!root.contains(propName))   return false;
    if (!root[propName].isDouble()) return false;
    
    auto value = root[propName].toDouble();
    
    propValue = value;
    
    return true;
}

QJsonObject TextKeyWordsExtractorContext::generateConfigFileJson()
{
    QJsonObject newConfigFileRoot{};
    
    newConfigFileRoot.insert(C_BANNED_WORDS_PROP_NAME, QJsonArray{});
    newConfigFileRoot.insert(C_EQUALITY_COEF_PROP_NAME, C_DEFAULT_EQUALITY_COEF);
    newConfigFileRoot.insert(C_MAX_KEY_WORDS_COUNT_PROP_NAME, static_cast<int>(C_DEFAULT_MAX_KEY_WORDS_COUNT)); 
    
    return newConfigFileRoot;
}
