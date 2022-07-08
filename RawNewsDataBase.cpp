#include "RawNewsDataBase.h"

RawNewsDataBase::RawNewsDataBase()
    : m_sourceType{AppContext::SourceType::ST_INVALID},
      m_data{}
{
    
}

RawNewsDataBase::RawNewsDataBase(const AppContext::SourceType type,
                                 const QByteArray &data)
    : m_sourceType{type},
      m_data{data}
{
    
}

AppContext::SourceType RawNewsDataBase::getSourceType() const
{
    return m_sourceType;
}

const QByteArray &RawNewsDataBase::getData() const
{
    return m_data;
}
