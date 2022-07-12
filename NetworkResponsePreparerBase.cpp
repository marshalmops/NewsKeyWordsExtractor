#include "NetworkResponsePreparerBase.h"

NetworkResponsePreparerBase::NetworkResponsePreparerBase(const std::shared_ptr<NetworkRequestExecutor> &executor)
    : m_executor{executor}
{
    
}
