#ifndef TEXTKEYWORDSEXTRACTORCONTEXT_H
#define TEXTKEYWORDSEXTRACTORCONTEXT_H

#include <QJsonObject>
#include <QJsonArray>

#include "FileManager.h"

class TextKeyWordsExtractorContext
{
    constexpr static const char* C_KEY_WORDS_EXTRACTOR_CONFIG_FILENAME = "key_words_extractor_config.json";
    constexpr static const char* C_BANNED_WORDS_PROP_NAME              = "banned_words";
    constexpr static const char* C_EQUALITY_COEF_PROP_NAME             = "equality_coef";
    
    constexpr static const float C_DEFAULT_EQUALITY_COEF = 0.76;

public:
    TextKeyWordsExtractorContext() = delete;
    
    static bool initializeContext(const std::shared_ptr<FileManager> &fileManager);
    
    static const std::shared_ptr<QStringList>& getBannedWordsList();
    static float getEqualityCoef();

private:
    static bool loadBannedWords(const QJsonObject &root);
    static QJsonObject generateConfigFileJson();
    
private:
    static std::shared_ptr<QStringList> m_bannedWordsList;
    static float                        m_equalityCoef;
};

#endif // TEXTKEYWORDSEXTRACTORCONTEXT_H
