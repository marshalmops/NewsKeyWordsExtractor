#ifndef RAWNEWSDATABASE_H
#define RAWNEWSDATABASE_H

#include "SourceDictionary.h"

class RawNewsDataBase
{
public:
    RawNewsDataBase();
    RawNewsDataBase(const SourceDictionary::SourceType type,
                    const QByteArray &data);
    
    SourceDictionary::SourceType getSourceType() const;
    const QByteArray&            getData      () const;
    
private:
    SourceDictionary::SourceType m_sourceType;
    QByteArray                   m_data;
};

#endif // RAWNEWSDATABASE_H
