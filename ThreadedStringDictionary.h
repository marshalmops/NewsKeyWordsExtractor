#ifndef THREADEDSTRINGDICTIONARY_H
#define THREADEDSTRINGDICTIONARY_H

#include <QString>
#include <vector>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

#include "AppContext.h"

#include "ThreadedStringDictionaryItem.h"
#include "ThreadedTransactionData.h"

namespace {

std::unique_lock<std::mutex> generateLock(std::mutex &mutex,
                                          std::shared_ptr<ThreadedTransactionData> &transactionData)
{
    if (!transactionData.get()) {
        if (!transactionData->getLock().owns_lock())
            transactionData = std::make_shared<ThreadedTransactionData>(std::unique_lock<std::mutex>{mutex});
        
        return std::unique_lock<std::mutex>{};
    }
    
    return std::unique_lock<std::mutex>{mutex};
}

};

template <class Value>
class ThreadedStringDictionary
{
private:
    bool searchIteration(const QString &key,
                         const ThreadedStringDictionaryItem<Value> &curItem,
                         ThreadedStringDictionaryItem<Value> *&foundItem,
                         const QString &curKey, 
                         const unsigned int depth = 0)
    {
        if (key == curKey) {
            foundItem = const_cast<ThreadedStringDictionaryItem<Value>*>(&curItem);
            
            return true;
        }
        
        auto &curNodes = const_cast<ThreadedStringDictionaryItem<Value>*>(&curItem)->getNodes();
        
        for (auto i = curNodes.begin(); i != curNodes.end(); ++i) {
            if (i->getChar() == key[depth]) 
                return searchIteration(key, *i, foundItem, curKey + key[depth], depth + 1);
        }
        
        foundItem = const_cast<ThreadedStringDictionaryItem<Value>*>(&curItem);
    
        return false;
    }
    
    bool addIteration(const QString &key,
                      std::unique_ptr<Value> &value,
                      ThreadedStringDictionaryItem<Value> &curItem,
                      const QString curKey = QString{},
                      const unsigned int depth = 0)
    {
        if (key == (curKey + key.back())) {
            curItem.changeValue(std::move(value));
            
            return true;
        }
        
        for (auto i = curItem.getNodes().begin(); i != curItem.getNodes().end(); ++i) {
            if (i->getChar() == key[depth])
                return addIteration(key, value, *i, curKey + key[depth], depth + 1);
        }
        
        ThreadedStringDictionaryItem<Value> *addedItem{nullptr};
        
        if (!(addedItem = curItem.addNode(key[depth], std::unique_ptr<Value>{nullptr}))) return false;
        
        return addIteration(key, value, *addedItem, curKey + key[depth], depth + 1);
    }
    
    void toJsonIteration(ThreadedStringDictionaryItem<AppContext::WordsFrequency> &curItem,
                         QJsonObject &jsonDictionary,
                         const QString curKey = QString{}) const
    {
        if (curItem.getValue().get())
            jsonDictionary[curKey] = static_cast<int>(*curItem.getValue()); //FIXME
        
        for (auto i = curItem.getNodes().begin(); i != curItem.getNodes().end(); ++i)
            toJsonIteration(*i, jsonDictionary, curKey + i->getChar());
    }
    
public:
    ThreadedStringDictionary()
        : m_root {std::make_unique<ThreadedStringDictionaryItem<Value>>()},
          m_mutex{}
    {
        
    }
    
    bool getClosestKey(const QString &key,
                       QString &closestKey,
                       std::shared_ptr<ThreadedTransactionData> transactionData)
    {
        std::unique_lock<std::mutex> lock = ::generateLock(m_mutex, transactionData);
        ThreadedStringDictionaryItem<Value> *closestItem{};
        
        return searchIteration(key, *m_root, closestItem, closestKey);
    }
    
    bool addItem(const QString &key, 
                 std::unique_ptr<Value> &&value,
                 std::shared_ptr<ThreadedTransactionData> transactionData)
    {
        std::unique_lock<std::mutex> lock = ::generateLock(m_mutex, transactionData);
        
        if (!addIteration(key, value, *m_root)) return false;
        
        return true;
    }
    
    bool changeValueOfKey(const QString &key, 
                          std::unique_ptr<Value> &&newValue,
                          std::shared_ptr<ThreadedTransactionData> transactionData)
    {
        std::unique_lock<std::mutex> lock = ::generateLock(m_mutex, transactionData);
        
        ThreadedStringDictionaryItem<Value> item  {};
        QString                             curKey{};
        
        if (!searchIteration(key, m_root, item, curKey)) return false;
        
        item.changeValue(newValue);
        
        return true;
    }
    
    bool incrementValueOfKey(const QString &key, 
                             std::shared_ptr<ThreadedTransactionData> transactionData)
    {
        std::unique_lock<std::mutex> lock = ::generateLock(m_mutex, transactionData);
        
        ThreadedStringDictionaryItem<AppContext::WordsFrequency> *item{nullptr};
        QString                                                   curKey{};
        
        if (!searchIteration(key, *m_root, item, curKey)) return false;
        
        item->changeValue(std::make_unique<AppContext::WordsFrequency>(*(item->getValue()) + 1));
        
        return true;
    }
    
    QJsonDocument toJson() const
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        
        QJsonObject jsonRootObj{};
        
        toJsonIteration(*m_root, jsonRootObj);
        
        return QJsonDocument{jsonRootObj};
    }
    
private:
    std::unique_ptr<ThreadedStringDictionaryItem<Value>> m_root;
    
    mutable std::mutex m_mutex;
};

#endif // THREADEDSTRINGDICTIONARY_H
