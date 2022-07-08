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
    ThreadedStringDictionaryItem()
        : m_char {},
          m_value{}
    {
        
    }
    
    ThreadedStringDictionaryItem(const QChar ch,
                                 std::unique_ptr<Value> &&value)
        : m_char {ch},
          m_value{value.release()}
    {
        
    }
    
    ~ThreadedStringDictionaryItem()
    {
        if (m_value) delete m_value;
    }
    
    QChar getChar() const
    {
        return m_char;
    }
    
    std::unique_ptr<Value> getValue() const
    {
        return std::make_unique<Value>(*(m_value));
    }
    
    void changeValue(std::unique_ptr<Value> &&newValue)
    {
        if (m_value) delete m_value;
        
        m_value = newValue.release();
    }
    
    std::vector<ThreadedStringDictionaryItem<Value>> &getNodes()
    {
        return m_nodes;
    }
    
    ThreadedStringDictionaryItem<Value> *addNode(const QChar ch, 
                                                 std::unique_ptr<Value> &&value)
    {
        if (!ch.isLetter()) return nullptr;
        
        for (auto i = m_nodes.begin(); i != m_nodes.end(); ++i)
            if (i->m_char == ch) return nullptr;
        
        m_nodes.push_back(ThreadedStringDictionaryItem{ch, std::move(value)});
        
        return &(m_nodes.back());
    }
    
private:
    QChar  m_char;
    Value* m_value;
    
    std::vector<ThreadedStringDictionaryItem<Value>> m_nodes;
};

#endif // THREADEDSTRINGDICTIONARYITEM_H
