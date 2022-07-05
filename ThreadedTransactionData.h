#ifndef THREADEDTRANSACTIONDATA_H
#define THREADEDTRANSACTIONDATA_H

#include <mutex>

class ThreadedTransactionData
{
public:
    ThreadedTransactionData();
    ThreadedTransactionData(std::unique_lock<std::mutex> &&transactionLock);
    
    std::unique_lock<std::mutex>& getLock();
    
    bool isTransactional() const;
    
private:
    std::unique_lock<std::mutex> m_transactionLock;
    
    bool m_isTransactional;
};

#endif // THREADEDTRANSACTIONDATA_H
