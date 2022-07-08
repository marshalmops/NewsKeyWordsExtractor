#include "TextKeyWordsExtractor.h"

namespace {

bool removeOtherSigns(QString &string) {
    if (string.isEmpty()) return false;
    
    QString stringBuffer{string};
    
    static const QString otherSigns{",;.'\"\\/~{[]}+-=*&^%$#@!?><:"};
    
    for (auto i = string.begin(); i != string.end(); ++i) {
        if (otherSigns.contains(*i)) continue;
        
        stringBuffer += *i;
    }
    
    string = std::move(stringBuffer);
    
    return true;
}

bool removeOtherWords(QString &string, QStringList &words) {
    if (string.isEmpty()) return false;
    
    QStringList wordsBuffer{};
    
    static const QStringList otherWords{"а", "но", "да", "или", "что", "как", "чтобы", "и", "либо", "то",
                                        "у", "о", "к", "в", "с", "от", "об", "до", "по", "под", "на", "над",
                                        "за", "из-за", "из-под", "перед", "через"};
    
    auto sourceWords = string.split(' ');
    
    foreach (const auto& sourceWord, sourceWords) {
        if (otherWords.contains(sourceWord)) continue;
        
        wordsBuffer += sourceWord;
    }
    
    words = std::move(wordsBuffer);
    
    return true;
}

}

bool TextKeyWordsExtractor::extractKeyWordsOfNews(const std::vector<News> &news,
                                                  std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency>> &dictionary)
{
    for (auto i = news.begin(); i != news.end(); ++i) {
        QStringList curNewsWords{};
        
        if (!prepareWords(i->getText(), curNewsWords)) return false;
        
        std::shared_ptr<ThreadedTransactionData> transactionData{};
        
        for (auto i = curNewsWords.begin(); i != curNewsWords.end(); ++i) {
            QString closestWord{};
            
            if (!dictionary->getClosestKey(*i, closestWord, transactionData)) return false;

            float equalityRate{0.};
            
            if (!getWordsEqualityRate(*i, closestWord, equalityRate)) return false;
            
            if (equalityRate >= C_EQUALITY_COEFFICIENT) {
                if (!dictionary->incrementValueOfKey(closestWord, transactionData)) 
                    return false;
            } else {
                if (!dictionary->addItem(closestWord, std::make_unique<AppContext::WordsFrequency>(1), transactionData))
                    return false;
            }
        }
    }
    
    return true;
}

bool TextKeyWordsExtractor::prepareWords(const QString &string, 
                                         QStringList &words)
{
    QString stringBuffer{string.toLower()};
    
    if (!removeOtherSigns(stringBuffer)) return false;
    
    QStringList wordsBuffer{};
    
    if (!removeOtherWords(stringBuffer, wordsBuffer)) return false;
    
    words = std::move(wordsBuffer);
    
    return true;
}

bool TextKeyWordsExtractor::getWordsEqualityRate(const QString &firstWord, 
                                                 const QString &secondWord, 
                                                 float &equalityRate)
{
    if (firstWord.isEmpty() || secondWord.isEmpty()) return false;
    
    auto shortestWordLength = (firstWord.length() < secondWord.length() ? firstWord.length() : secondWord.length());
    uint32_t equalSignsSequenceLength{0};
    
    for (auto i = 0; i < shortestWordLength; ++i) {
        if (firstWord.at(i) == secondWord.at(i)) ++equalSignsSequenceLength;
        else if (equalSignsSequenceLength > 0) break;
    }
    
    auto longestWordLength = (firstWord.length() > secondWord.length() ? firstWord.length() : secondWord.length());
    
    equalityRate = equalSignsSequenceLength / static_cast<float>(longestWordLength);
    
    return true;
}
