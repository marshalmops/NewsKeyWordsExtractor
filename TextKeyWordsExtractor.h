#ifndef TEXTKEYWORDSEXTRACTOR_H
#define TEXTKEYWORDSEXTRACTOR_H

#include "AppContext.h"

#include "ThreadedStringDictionary.h"

#include <News.h>

class TextKeyWordsExtractor
{
    constexpr static const float C_EQUALITY_COEFFICIENT = 0.76;
    
public:
    TextKeyWordsExtractor();
    
    bool extractKeyWordsOfNews(const std::vector<News> &news,
                               std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency>> &dictionary);

private:
    bool prepareWords(const QString &string, 
                      QStringList &words);
    bool getWordsEqualityRate(const QString &firstWord,
                              const QString &secondWord,
                              float &equalityRate);
};

#endif // TEXTKEYWORDSEXTRACTOR_H
