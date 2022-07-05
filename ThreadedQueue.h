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
    
private:
    std::queue<T> m_queue;
    
    std::mutex m_frontMutex;
    std::mutex m_backMutex;
};

#endif // THREADEDQUEUE_H
