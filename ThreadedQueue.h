#ifndef THREADEDQUEUE_H
#define THREADEDQUEUE_H

#include <mutex>
#include <queue>

template <class T>
class ThreadedQueue
{
public:
    ThreadedQueue();
    
    void pushItem(T&& item);
    bool takeItem(T& item);
    
    bool isEmpty() const;
    
private:
    std::queue<T> m_queue;
    
    mutable std::mutex m_frontMutex;
    mutable std::mutex m_backMutex;
};

#endif // THREADEDQUEUE_H
