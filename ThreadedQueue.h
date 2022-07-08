#ifndef THREADEDQUEUE_H
#define THREADEDQUEUE_H

#include <mutex>
#include <queue>

template <class T>
class ThreadedQueue
{
public:
    ThreadedQueue()
        : m_queue{},
          m_frontMutex{},
          m_backMutex{}
    {
        
    }
    
    void pushItem(T &&item)
    {
        std::unique_lock<std::mutex> lock{m_backMutex};
        
        m_queue.push(std::move(item));
    }
    
    bool takeItem(T &item)
    {
        std::unique_lock<std::mutex> lock{m_frontMutex};
        
        if (m_queue.empty()) return false;
        
        item = std::move(m_queue.front());
        
        m_queue.pop();
        
        return true;
    }
    
    bool isEmpty() const
    {
        std::unique_lock<std::mutex> lockFront{m_frontMutex};
        std::unique_lock<std::mutex> lockBack {m_backMutex};
        
        return m_queue.empty();
    }
    
private:
    std::queue<T> m_queue;
    
    mutable std::mutex m_frontMutex;
    mutable std::mutex m_backMutex;
};

#endif // THREADEDQUEUE_H
