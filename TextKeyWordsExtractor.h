#ifndef TEXTKEYWORDSEXTRACTOR_H
#define TEXTKEYWORDSEXTRACTOR_H

#include <algorithm>

#include "AppContext.h"
#include "TextKeyWordsExtractorContext.h"

#include "ThreadedStringDictionary.h"

#include "News.h"

class TextKeyWordsExtractor
{
    constexpr static const uint32_t C_MAX_KEY_WORDS_COUNT = 10;
    
public:
    TextKeyWordsExtractor() = default;
    
    bool extractKeyWordsOfNews(const News &news,
                               std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency>> &dictionary);

private:
    bool prepareWords(const QString &string, 
                      QStringList &words);
    bool getWordsEqualityRate(const QString &firstWord,
                              const QString &secondWord,
                              float &equalityRate);
    
    bool getTopKeyWordsVector   (StringDictionary<AppContext::WordsFrequency>::StringValueVector &keyWordsVector);
    bool putKeyWordsToRemoteDictionary(const StringDictionary<AppContext::WordsFrequency>::StringValueVector &vector,
                                       std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency>> &dictionary);
    bool putKeyWordsToLocalDictionary(const QStringList &words);
    
private:
    StringDictionary<AppContext::WordsFrequency> m_localDictionary;
};

#endif // TEXTKEYWORDSEXTRACTOR_H
