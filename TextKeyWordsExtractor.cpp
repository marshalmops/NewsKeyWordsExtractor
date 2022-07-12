#include "TextKeyWordsExtractor.h"

namespace {

bool removeOtherSigns(QString &string) {
    if (string.isEmpty()) return false;
    
    QString stringBuffer{};
    
    stringBuffer = string.remove(QRegExp{"[^A-Za-zА-Яа-я\\s]"});
    
    string = std::move(stringBuffer);
    
    return true;
}

bool removeOtherWords(QString &string, 
                      QStringList &words) {
    if (string.isEmpty()) return false;
    
    QStringList wordsBuffer{};
    
    const auto &bannedWordsList = TextKeyWordsExtractorContext::getBannedWordsList();
    
//    static const QStringList otherWords{"а", "но", "да", "или", "что", "как", "чтобы", "и", "либо", "то",
//                                        "у", "о", "к", "в", "с", "от", "об", "обо", "до", "по", "под", "на", "над",
//                                        "за", "из-за", "из-под", "перед", "через", "из", "для", "мы", "они", 
//                                        "вы", "их", "им", "ими", "них" "я", "он", "она", "ей", "ее", "её", 
//                                        "ему", "им", "вас", "вам", "вами", "меня", "мне", "мной", "ним", "них", 
//                                        "его", "нем", "нём", "ней", "ты", "тебя", "тебе", "тобой", "мы", "нас", 
//                                        "нам", "нами", "оно", "так", "же", "также", "не", "нет", "это",
//                                        "такой", "какой", "некий", "во", "при", "чем", "затем", "зачем",
//                                        "однако", "эти", "этого", "этой", "этот", "эту", "этом", "этим",
//                                        "уже", "туда", "тем", "том", "самих", "самых", "самой", "сам", "сама"};
    
    auto sourceWords = string.simplified().split(' ');
    
    foreach (const auto& sourceWord, sourceWords) {
        if (bannedWordsList->contains(sourceWord)) continue;
        
        wordsBuffer += sourceWord;
    }
    
    words = std::move(wordsBuffer);
    
    return true;
}

}

bool TextKeyWordsExtractor::extractKeyWordsOfNews(const News &news,
                                                  std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency>> &dictionary)
{
    m_localDictionary.reset();
    
    QStringList curNewsWords{};
        
    if (!prepareWords(news.getText(), curNewsWords)) return false;
    if (!putKeyWordsToLocalDictionary(curNewsWords)) return false;
    
    StringDictionary<AppContext::WordsFrequency>::StringValueVector keyWordsVector{};
    
    if (!getTopKeyWordsVector(keyWordsVector))                      return false;
    if (!putKeyWordsToRemoteDictionary(keyWordsVector, dictionary)) return false;
    
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

bool TextKeyWordsExtractor::getTopKeyWordsVector(StringDictionary<AppContext::WordsFrequency>::StringValueVector &keyWordsVector)
{
    StringDictionary<AppContext::WordsFrequency>::StringValueVector bufVector{};
    
    m_localDictionary.toVector(bufVector);
    
    if (bufVector.empty()) 
        return false;
    
    std::sort(bufVector.begin(), bufVector.end(), [&](const StringDictionary<AppContext::WordsFrequency>::StringValueVectorItem &firstItem, 
                                                      const StringDictionary<AppContext::WordsFrequency>::StringValueVectorItem &secondItem)
    {
        return firstItem.second < secondItem.second;
    });
    
    keyWordsVector = std::move(bufVector);
    
    return true;
}

bool TextKeyWordsExtractor::putKeyWordsToRemoteDictionary(const StringDictionary<AppContext::WordsFrequency>::StringValueVector &vector,
                                                          std::shared_ptr<ThreadedStringDictionary<AppContext::WordsFrequency>> &dictionary)
{
    if (vector.empty()) 
        return false;
    
    std::shared_ptr<ThreadedTransactionData> transactionData{};
    
    for (auto i = 0; (i < C_MAX_KEY_WORDS_COUNT) && (i < vector.size()); ++i) {
        QString                    curWord     {vector.at(i).first};
        AppContext::WordsFrequency curFrequency{vector.at(i).second};
        
        QString closestWord{};
        
        if (dictionary->getClosestKey(curWord, closestWord, transactionData)) {
            if (!dictionary->incrementValueOfKey(closestWord, transactionData)) 
                return false;
            
            continue;
        }
        
        if (closestWord.isEmpty()) {
            if (!dictionary->addItem(curWord, std::make_unique<AppContext::WordsFrequency>(1), transactionData))
                return false;
            
            continue;
        }
        
        float equalityRate{0.};
        
        if (!getWordsEqualityRate(curWord, closestWord, equalityRate)) 
            return false;
        
        if (equalityRate >= TextKeyWordsExtractorContext::getEqualityCoef()) {
            if (!dictionary->incrementValueOfKey(closestWord, transactionData, curFrequency)) 
                return false;
        } else {
            if (!dictionary->addItem(curWord, std::make_unique<AppContext::WordsFrequency>(1), transactionData))
                return false;
        }
    }
    
    return true;
}

bool TextKeyWordsExtractor::putKeyWordsToLocalDictionary(const QStringList &words)
{
    if (words.isEmpty()) return false;
    
    for (auto i = words.begin(); i != words.end(); ++i) {
        QString closestWord{};
        
        if (m_localDictionary.getClosestKey(*i, closestWord)) {
            if (!m_localDictionary.incrementValueOfKey(closestWord)) 
                return false;
            
            continue;
        }
        
        if (closestWord.isEmpty()) {
            if (!m_localDictionary.addItem(*i, std::make_unique<AppContext::WordsFrequency>(1)))
                return false;
            
            continue;
        }
        
        float equalityRate{0.};
        
        if (!getWordsEqualityRate(*i, closestWord, equalityRate)) 
            return false;
        
        if (equalityRate >= TextKeyWordsExtractorContext::getEqualityCoef()) {
            if (!m_localDictionary.incrementValueOfKey(closestWord)) 
                return false;
        } else {
            if (!m_localDictionary.addItem(*i, std::make_unique<AppContext::WordsFrequency>(1)))
                return false;
        }
    }
    
    return true;
}
