#ifndef STRINGDICTIONARYITEM_H
#define STRINGDICTIONARYITEM_H

#include <shared_mutex>
#include <memory>
#include <vector>
#include <QChar>

template <class Value>
class StringDictionaryItem
{
public:
    StringDictionaryItem()
        : m_char {},
          m_value{nullptr},
          m_nodes{}
    {
        
    }
    
    StringDictionaryItem(const QChar ch,
                                 const std::shared_ptr<Value> &value)
        : m_char {ch},
          m_value{value},
          m_nodes{}
    {
        
    }
    
    StringDictionaryItem(const StringDictionaryItem& other)
        : m_char {other.m_char},
          m_value{other.m_value},
          m_nodes{std::move(other.m_nodes)}
    {
        
    }
    
    ~StringDictionaryItem()
    {
        
    }
    
    QChar getChar() const
    {
        return m_char;
    }
    
    const std::shared_ptr<Value>& getValue() const
    {
        return m_value;
    }
    
    void changeValue(std::unique_ptr<Value> &&newValue)
    {
        m_value = std::shared_ptr<Value>(newValue.release());
    }
    
    std::vector<StringDictionaryItem<Value>> &getNodes()
    {
        return m_nodes;
    }
    
    StringDictionaryItem<Value> *addNode(const QChar ch, 
                                                 std::unique_ptr<Value> &&value)
    {
        if (!ch.isLetter() && ch != '_') 
            return nullptr;
        
        for (auto i = m_nodes.begin(); i != m_nodes.end(); ++i)
            if (i->m_char == ch) 
                return nullptr;
        
        std::shared_ptr<Value> valueShared{(value.get() ? value.release() : nullptr)};
        
        m_nodes.push_back(StringDictionaryItem{ch, valueShared});
        
        return &(m_nodes.back());
    }
    
private:
    QChar  m_char;
    std::shared_ptr<Value> m_value;
    
    std::vector<StringDictionaryItem<Value>> m_nodes;
};

#endif // STRINGDICTIONARYITEM_H
