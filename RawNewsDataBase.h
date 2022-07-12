#ifndef RAWNEWSDATABASE_H
#define RAWNEWSDATABASE_H

#include <QMetaType>

#include "AppContext.h"

#include "SourceBase.h"

class RawNewsDataBase
{
public:
    RawNewsDataBase();
    RawNewsDataBase(const std::shared_ptr<SourceBase> &source,
                    const QByteArray &data);
    
    std::shared_ptr<SourceBase> getSource() const;
    const QByteArray&           getData  () const;
    
private:
    std::shared_ptr<SourceBase> m_sourcePtr;
    QByteArray                  m_data;
};

Q_DECLARE_METATYPE(RawNewsDataBase)

#endif // RAWNEWSDATABASE_H
