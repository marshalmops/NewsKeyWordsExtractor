#ifndef STRINGDICTIONARY_H
#define STRINGDICTIONARY_H


#include <QString>
#include <vector>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

#include "AppContext.h"

#include "StringDictionaryItem.h"

template <class Value>
class StringDictionary
{
private:
    bool searchIteration(const QString &key,
                         const StringDictionaryItem<Value> &curItem,
                         StringDictionaryItem<Value> *&foundItem,
                         QString &foundItemKey,
                         const QString &curKey = QString{}, 
                         const unsigned int depth = 0)
    {
        if (key == curKey) {
            auto curItemNonConst = const_cast<StringDictionaryItem<Value>*>(&curItem);
            
            if (curItemNonConst->getNodes().empty()) {
                foundItem    = curItemNonConst;
                foundItemKey = curKey;
                
                return true;
                
            } else {
                return getShortestNode(key, curItemNonConst, foundItem, foundItemKey);
            }
        }
        
        auto &curNodes = const_cast<StringDictionaryItem<Value>*>(&curItem)->getNodes();
        
        for (auto i = curNodes.begin(); i != curNodes.end(); ++i) {
            if (i->getChar() == key[depth]) 
                return searchIteration(key, *i, foundItem, foundItemKey, curKey + key[depth], depth + 1);
        }
        
        foundItem    = const_cast<StringDictionaryItem<Value>*>(&curItem);
        foundItemKey = curKey;
    
        return false;
    }
    
    bool getShortestNode(const QString &key,
                         StringDictionaryItem<Value> *startItem,
                         StringDictionaryItem<Value> *&foundItem,
                         QString &foundItemKey) 
    {
        std::vector<std::pair<QString, StringDictionaryItem<Value>*>> nodes{};
        
        if (!getShortestNodeIteration(key, startItem, nodes)) return false;
        
        auto shortestNodePtr = nodes.begin();
        
        for (auto i = nodes.begin(); i != nodes.end(); ++i) {
            if (i->first.length() < shortestNodePtr->first.length())
                shortestNodePtr = i;
        }
        
        if (shortestNodePtr == nodes.end()) return false;
        
        foundItem = shortestNodePtr->second;
        foundItemKey = shortestNodePtr->first;
        
        return true;
    }
    
    bool getShortestNodeIteration(const QString &curKey,
                                  StringDictionaryItem<Value> *curItem,
                                  std::vector<std::pair<QString, StringDictionaryItem<Value>*>> &nodes)
    {
        if (!curItem) return false;
        
        if (curItem->getValue().get()) {
            nodes.push_back(std::pair<QString, StringDictionaryItem<Value>*>(curKey, curItem));
        }
        
        for (auto i = curItem->getNodes().begin(); i != curItem->getNodes().end(); ++i) {
            bool resultFlag{getShortestNodeIteration(curKey + i->getChar(), &(*i), nodes)};
            
            if (!resultFlag) return false;
        }
        
        return true;
    }
    
    bool addIteration(const QString &key,
                      std::unique_ptr<Value> &value,
                      StringDictionaryItem<Value> &curItem,
                      const QString curKey = QString{},
                      const unsigned int depth = 0)
    {
        if (key == curKey) {
            curItem.changeValue(std::move(value));
            
            return true;
        }
        
        for (auto i = curItem.getNodes().begin(); i != curItem.getNodes().end(); ++i) {
            if (i->getChar() == key[depth])
                return addIteration(key, value, *i, curKey + key[depth], depth + 1);
        }
        
        StringDictionaryItem<Value> *addedItem{nullptr};
        
        if (!(addedItem = curItem.addNode(key[depth], std::unique_ptr<Value>{nullptr}))) 
            return false;
        
        return addIteration(key, value, *addedItem, curKey + key[depth], depth + 1);
    }
    
    void toJsonIteration(StringDictionaryItem<AppContext::WordsFrequency> &curItem,
                         QJsonObject &jsonDictionary,
                         const QString curKey = QString{}) const
    {
        if (curItem.getValue().get())
            jsonDictionary[curKey] = static_cast<int>(*curItem.getValue()); //FIXME
        
        for (auto i = curItem.getNodes().begin(); i != curItem.getNodes().end(); ++i)
            toJsonIteration(*i, jsonDictionary, curKey + i->getChar());
    }
    
    void toVectorIteration(StringDictionaryItem<AppContext::WordsFrequency> &curItem,
                           std::vector<std::pair<QString, Value>> &vector,
                           const QString curKey = QString{}) const
    {
        if (curItem.getValue().get())
            vector.push_back(std::pair<QString, Value>{curKey, *(curItem.getValue())});
        
        for (auto i = curItem.getNodes().begin(); i != curItem.getNodes().end(); ++i)
            toVectorIteration(*i, vector, curKey + i->getChar());
    }
    
public:
    using StringValueVectorItem = std::pair<QString, AppContext::WordsFrequency>;
    using StringValueVector = std::vector<StringValueVectorItem>;
    
    StringDictionary()
        : m_root {std::make_unique<StringDictionaryItem<Value>>()}
    {
        
    }
    
    bool getClosestKey(const QString &key,
                       QString &closestKey)
    {
        StringDictionaryItem<Value> *closestItem{};
        
        return searchIteration(key, *m_root, closestItem, closestKey);
    }
    
    bool addItem(const QString &key, 
                 std::unique_ptr<Value> &&value)
    {
        if (!addIteration(key, value, *m_root)) return false;
        
        return true;
    }
    
    bool changeValueOfKey(const QString &key, 
                          std::unique_ptr<Value> &&newValue)
    {
        StringDictionaryItem<Value> item  {};
        QString                     curKey{};
        
        if (!searchIteration(key, m_root, item, curKey)) return false;
        
        item.changeValue(newValue);
        
        return true;
    }
    
    bool incrementValueOfKey(const QString &key,
                             const uint64_t &incrementValue = 1)
    {
        StringDictionaryItem<AppContext::WordsFrequency> *item{nullptr};
        QString                                           curKey{};
        
        if (!searchIteration(key, *m_root, item, curKey)) return false;
        
        item->changeValue(std::make_unique<AppContext::WordsFrequency>(*(item->getValue()) + incrementValue));
        
        return true;
     }
                                                               
    QJsonDocument toJson() const
    {
        QJsonObject jsonRootObj{};
        
        toJsonIteration(*m_root, jsonRootObj);
        
        return QJsonDocument{jsonRootObj};
    }
    
    void toVector(std::vector<std::pair<QString, Value>> &vector) const {
        toVectorIteration(*m_root, vector);
    }
    
    void reset() {
        m_root.reset(std::make_unique<StringDictionaryItem<Value>>().release());
    }
    
protected:
    std::unique_ptr<StringDictionaryItem<Value>> m_root;
};


#endif // STRINGDICTIONARY_H
