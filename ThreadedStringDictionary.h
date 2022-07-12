#ifndef THREADEDSTRINGDICTIONARY_H
#define THREADEDSTRINGDICTIONARY_H

#include "AppContext.h"

#include "StringDictionary.h"
#include "StringDictionaryItem.h"

#include "ThreadedTransactionData.h"

namespace {

void generateLock(std::mutex &mutex,
                  std::shared_ptr<ThreadedTransactionData> &transactionData)
{
    if (transactionData.get()) {
        if (!transactionData->getLock().owns_lock())
            transactionData = std::make_shared<ThreadedTransactionData>(std::unique_lock<std::mutex>{mutex});
        
        return;
    }
    
    transactionData = std::make_shared<ThreadedTransactionData>(std::unique_lock<std::mutex>{mutex});
    
    return;
}

};

template <class Value>
class ThreadedStringDictionary : protected StringDictionary<Value>
{
public:
    ThreadedStringDictionary()
        : StringDictionary<Value>{},
          m_mutex{}
    {
        
    }
    
    bool getClosestKey(const QString &key,
                       QString &closestKey,
                       std::shared_ptr<ThreadedTransactionData> transactionData)
    {
        ::generateLock(m_mutex, transactionData);
        
        return StringDictionary<Value>::getClosestKey(key, closestKey);
    }
    
    bool addItem(const QString &key, 
                 std::unique_ptr<Value> &&value,
                 std::shared_ptr<ThreadedTransactionData> &transactionData)
    {
        ::generateLock(m_mutex, transactionData);
        
        return StringDictionary<Value>::addItem(key, std::move(value));
    }
    
    bool changeValueOfKey(const QString &key, 
                          std::unique_ptr<Value> &&newValue,
                          std::shared_ptr<ThreadedTransactionData> transactionData)
    {
        ::generateLock(m_mutex, transactionData);
        
        return StringDictionary<Value>::changeValueOfKey(key, std::move(newValue));
    }
    
    bool incrementValueOfKey(const QString &key,
                             std::shared_ptr<ThreadedTransactionData> transactionData,
                             const uint64_t &incrementValue = 1)
    {
        ::generateLock(m_mutex, transactionData);
        
        return StringDictionary<Value>::incrementValueOfKey(key, incrementValue);
    }
    
    QJsonDocument toJson() const
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        
        return StringDictionary<Value>::toJson();
    }
    
private:
    mutable std::mutex m_mutex;
};

#endif // THREADEDSTRINGDICTIONARY_H
