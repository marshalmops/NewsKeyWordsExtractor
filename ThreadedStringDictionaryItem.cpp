#include "ThreadedStringDictionaryItem.h"

template<class Value>
ThreadedStringDictionaryItem<Value>::ThreadedStringDictionaryItem()
    : m_char {},
      m_value{}
    //,m_mutex{}
{
    
}

template<class Value>
ThreadedStringDictionaryItem<Value>::ThreadedStringDictionaryItem(const QChar ch,
                                                                  std::unique_ptr<Value> &value)
    : m_char {ch},
      m_value{value.release()}
    //,m_mutex{}
{
    
}

template<class Value>
QChar ThreadedStringDictionaryItem<Value>::getChar() const
{
    return m_char;
}

template<class Value>
std::unique_ptr<Value> ThreadedStringDictionaryItem<Value>::getValue() const
{
    //std::shared_lock<std::shared_mutex> lock(m_mutex);
    
    return std::make_unique<Value>(*(m_value.get()));
}

template<class Value>
void ThreadedStringDictionaryItem<Value>::changeValue(std::unique_ptr<Value> &newValue)
{
    //std::unique_lock<std::shared_mutex> lock(m_mutex);
    
    m_value = newValue.release();
}

template<class Value>
const std::vector<ThreadedStringDictionaryItem<Value>> &ThreadedStringDictionaryItem<Value>::getNodes() const
{
    return m_nodes;
}

template<class Value>
ThreadedStringDictionaryItem<Value> *ThreadedStringDictionaryItem<Value>::addNode(const QChar ch, 
                                                                                  std::unique_ptr<Value> &&value)
{
    //std::unique_lock<std::shared_mutex> lock(m_mutex);
    
    if (!ch.isLetter()) return nullptr;
    
    for (auto i = m_nodes.begin(); i != m_nodes.end(); ++i)
        if (i->m_char == ch) return nullptr;
    
    m_nodes.push_back(std::make_unique<ThreadedStringDictionaryItem>(ch, value));
    
    return &(m_nodes.back());
}
