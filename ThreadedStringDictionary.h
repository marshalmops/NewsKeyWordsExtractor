#ifndef THREADEDSTRINGDICTIONARY_H
#define THREADEDSTRINGDICTIONARY_H

#include <QString>
#include <vector>
#include <QJsonObject>
#include <QJsonValue>

#include "AppContext.h"

#include "ThreadedStringDictionaryItem.h"
#include "ThreadedTransactionData.h"

template <class Value>
class ThreadedStringDictionary
{
public:
    ThreadedStringDictionary();
    
    bool getClosestKey    (const QString &key, 
                           QString &closestKey,
                           std::shared_ptr<ThreadedTransactionData> transactionData = nullptr) const;
    bool addItem          (const QString &key,
                           std::unique_ptr<Value> &&value,
                           std::shared_ptr<ThreadedTransactionData> transactionData = nullptr);
    bool changeValueOfKey (const QString &key,
                           std::unique_ptr<Value> &&newValue,
                           std::shared_ptr<ThreadedTransactionData> transactionData = nullptr);
    bool incrementValueOfKey(const QString &key,
                             std::shared_ptr<ThreadedTransactionData> transactionData = nullptr);
    
    QJsonObject&& toJson() const;
    
private:
    bool searchIteration(const QString &key,
                         const ThreadedStringDictionaryItem<Value> &curItem,
                         ThreadedStringDictionaryItem<Value> *&foundItem,
                         const QString &curKey,
                         const unsigned int depth = 0);
    bool addIteration(const QString &key,
                      std::unique_ptr<Value> &value,
                      ThreadedStringDictionaryItem<Value> &curItem,
                      const QString curKey = QString{},
                      const unsigned int depth = 0);
    
    void toJsonIteration(const ThreadedStringDictionaryItem<AppContext::WordsFrequency> &curItem,
                         QJsonObject &jsonDictionary,
                         const QString curKey = QString{}) const;
    
private:
    std::unique_ptr<ThreadedStringDictionaryItem<Value>> m_root;
    
    mutable std::mutex m_mutex;
};

#endif // THREADEDSTRINGDICTIONARY_H
