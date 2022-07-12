#include "RawNewsDataBase.h"

RawNewsDataBase::RawNewsDataBase()
    : m_sourcePtr{nullptr},
      m_data{}
{
    
}

RawNewsDataBase::RawNewsDataBase(const std::shared_ptr<SourceBase> &source, 
                                 const QByteArray &data)
    : m_sourcePtr{source},
      m_data{data}
{
    
}

std::shared_ptr<SourceBase> RawNewsDataBase::getSource() const
{
    return m_sourcePtr;
}

const QByteArray &RawNewsDataBase::getData() const
{
    return m_data;
}
