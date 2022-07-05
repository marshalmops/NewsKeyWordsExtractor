#include "ThreadedStringDictionary.h"

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

template<class Value>
ThreadedStringDictionary<Value>::ThreadedStringDictionary()
    : m_root {std::make_unique<ThreadedStringDictionaryItem<Value>>()},
      m_mutex{}
{
    
}

template<class Value>
bool ThreadedStringDictionary<Value>::getClosestKey(const QString &key,
                                                    QString &closestKey,
                                                    std::shared_ptr<ThreadedTransactionData> transactionData) const
{
    std::unique_lock<std::mutex> lock = ::generateLock(m_mutex, transactionData);
    ThreadedStringDictionaryItem<Value> closestItem{};
    
    return searchIteration(key, m_root, closestItem, closestKey);
}

template<class Value>
bool ThreadedStringDictionary<Value>::addItem(const QString &key, 
                                              std::unique_ptr<Value> &value,
                                              std::shared_ptr<ThreadedTransactionData> transactionData)
{
    std::unique_lock<std::mutex> lock = ::generateLock(m_mutex, transactionData);
    
    if (!addIteration(key, value, m_root)) return false;
    
    return true;
}

template<class Value>
bool ThreadedStringDictionary<Value>::changeValueOfKey(const QString &key, 
                                                       std::unique_ptr<Value> &newValue,
                                                       std::shared_ptr<ThreadedTransactionData> transactionData)
{
    std::unique_lock<std::mutex> lock = ::generateLock(m_mutex, transactionData);
    
    ThreadedStringDictionaryItem<Value> item  {};
    QString                             curKey{};
    
    if (!searchIteration(key, m_root, item, curKey)) return false;
    
    item.changeValue(newValue);
    
    return true;
}

template<>
QJsonObject&& ThreadedStringDictionary<uint64_t>::toJson() const
{
    std::unique_lock<std::mutex> lock{m_mutex};
    
    QJsonObject jsonDictionary{};
    
    toJsonIteration(*m_root, jsonDictionary);
    
    return std::move(jsonDictionary);
}

template<class Value>
bool ThreadedStringDictionary<Value>::searchIteration(const QString &key,
                                                      ThreadedStringDictionaryItem<Value> &curItem,
                                                      ThreadedStringDictionaryItem<Value> &foundItem,
                                                      QString &curKey, 
                                                      const unsigned int depth)
{
    if (key == curKey) {
        foundItem  = curItem;
        
        return true;
    }
    
    const auto &curNodes = curItem.getNodes();
    
    for (auto i = curNodes.begin(); i != curNodes.end(); ++i) {
        if (i->getChar() == key[depth]) 
            return searchIteration(key, depth + 1, curKey + key[depth], foundItem);
    }
    
    foundItem = curItem;

    return false;
}

template<class Value>
bool ThreadedStringDictionary<Value>::addIteration(const QString &key,
                                                   std::unique_ptr<Value> &value,
                                                   ThreadedStringDictionaryItem<Value> &curItem,
                                                   const QString curKey,
                                                   const unsigned int depth)
{
    if (key == (curKey + key.back())) {
        curItem.changeValue(value);
        
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

template<class Value>
void ThreadedStringDictionary<Value>::toJsonIteration(const ThreadedStringDictionaryItem<uint64_t> &curItem,
                                                      QJsonObject &jsonDictionary,
                                                      const QString curKey) const
{
    if (curItem.getValue().get())
        jsonDictionary[curKey] = static_cast<int>(*curItem.getValue()); //FIXME
    
    for (auto i = curItem.getNodes().begin(); i != curItem.getNodes().end(); ++i)
        toJsonIteration(*i, jsonDictionary, curKey + i->getChar());
}
