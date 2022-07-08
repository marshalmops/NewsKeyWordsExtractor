#ifndef RAWNEWSDATABASE_H
#define RAWNEWSDATABASE_H

#include "AppContext.h"

class RawNewsDataBase
{
public:
    RawNewsDataBase();
    RawNewsDataBase(const AppContext::SourceType type,
                    const QByteArray &data);
    
    AppContext::SourceType getSourceType() const;
    const QByteArray&      getData      () const;
    
private:
    AppContext::SourceType m_sourceType;
    QByteArray             m_data;
};

#endif // RAWNEWSDATABASE_H
