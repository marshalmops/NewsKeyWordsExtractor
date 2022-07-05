#ifndef THREADEDSTRINGDICTIONARY_H
#define THREADEDSTRINGDICTIONARY_H

#include <QString>
#include <vector>
#include <QJsonObject>
#include <QJsonValue>

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
                           std::unique_ptr<Value> &value,
                           std::shared_ptr<ThreadedTransactionData> transactionData = nullptr);
    bool changeValueOfKey (const QString &key,
                           std::unique_ptr<Value> &newValue,
                           std::shared_ptr<ThreadedTransactionData> transactionData = nullptr);
    
    QJsonObject&& toJson() const;
    
private:
    bool searchIteration(const QString &key,
                         ThreadedStringDictionaryItem<Value> &curItem,
                         ThreadedStringDictionaryItem<Value> &foundItem,
                         QString &curKey,
                         const unsigned int depth = 0);
    bool addIteration(const QString &key,
                      std::unique_ptr<Value> &value,
                      ThreadedStringDictionaryItem<Value> &curItem,
                      const QString curKey = QString{},
                      const unsigned int depth = 0);
    
    void toJsonIteration(const ThreadedStringDictionaryItem<uint64_t> &curItem,
                         QJsonObject &jsonDictionary,
                         const QString curKey = QString{}) const;
    
private:
    std::unique_ptr<ThreadedStringDictionaryItem<Value>> m_root;
    
    mutable std::mutex m_mutex;
};

#endif // THREADEDSTRINGDICTIONARY_H
