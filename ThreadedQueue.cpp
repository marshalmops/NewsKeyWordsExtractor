#include "ThreadedQueue.h"


template<class T>
ThreadedQueue<T>::ThreadedQueue()
    : m_queue{},
      m_frontMutex{},
      m_backMutex{}
{
    
}

template<class T>
void ThreadedQueue<T>::pushItem(T &&item)
{
    std::unique_lock<std::mutex> lock{m_backMutex};
    
    m_queue.push(std::move(item));
}

template<class T>
bool ThreadedQueue<T>::takeItem(T &item)
{
    std::unique_lock<std::mutex> lock{m_frontMutex};
    
    if (m_queue.empty()) return false;
    
    item = std::move(m_queue.front());
    
    m_queue.pop();
    
    return true;
}

template<class T>
bool ThreadedQueue<T>::isEmpty() const
{
    std::unique_lock<std::mutex> lockFront{m_frontMutex};
    std::unique_lock<std::mutex> lockBack {m_backMutex};
    
    return m_queue.empty();
}
