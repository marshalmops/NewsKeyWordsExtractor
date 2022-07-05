#include "ThreadedTransactionData.h"

ThreadedTransactionData::ThreadedTransactionData()
    : m_transactionLock{},
      m_isTransactional{false}
{
    
}

ThreadedTransactionData::ThreadedTransactionData(std::unique_lock<std::mutex> &&transactionLock)
    : m_transactionLock{std::move(transactionLock)},
      m_isTransactional{true}
{
    
}

std::unique_lock<std::mutex> &ThreadedTransactionData::getLock()
{
    return m_transactionLock;
}

bool ThreadedTransactionData::isTransactional() const
{
    return m_isTransactional;
}
