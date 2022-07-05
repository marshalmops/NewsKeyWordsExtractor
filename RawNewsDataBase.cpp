#include "RawNewsDataBase.h"

RawNewsDataBase::RawNewsDataBase(const SourceDictionary::SourceType type,
                                 const QByteArray &data)
    : m_sourceType{type},
      m_data{data}
{
    
}

SourceDictionary::SourceType RawNewsDataBase::getSourceType() const
{
    return m_sourceType;
}

const QByteArray &RawNewsDataBase::getData() const
{
    return m_data;
}
