#ifndef THREADEDSTRINGDICTIONARYITEM_H
#define THREADEDSTRINGDICTIONARYITEM_H

#include <shared_mutex>
#include <memory>
#include <vector>
#include <QChar>

template <class Value>
class ThreadedStringDictionaryItem
{
public:
    ThreadedStringDictionaryItem();
    ThreadedStringDictionaryItem(const QChar ch,
                                 std::unique_ptr<Value> &&value);
    
    QChar                                                   getChar    () const;
    std::unique_ptr<Value>                                  getValue   () const;
    void                                                    changeValue(std::unique_ptr<Value> &&newValue);
    const std::vector<ThreadedStringDictionaryItem<Value>>& getNodes   () const;
    
    ThreadedStringDictionaryItem<Value>* addNode(const QChar ch, 
                                                 std::unique_ptr<Value> &&value);
    
private:
    QChar                  m_char;
    std::unique_ptr<Value> m_value;
    
    std::vector<ThreadedStringDictionaryItem<Value>> m_nodes;
};

#endif // THREADEDSTRINGDICTIONARYITEM_H
