#include "SourceStandardRSS.h"

SourceStandardRSS::SourceStandardRSS()
    : SourceBase{}
{
    
}

SourceStandardRSS::SourceStandardRSS(const QUrl &url,
                                     const AppContext::Id id)
    : SourceBase{url, id}
{
    
}

AppContext::SourceType SourceStandardRSS::getType() const
{
    return AppContext::SourceType::ST_STANDARD_RSS;
}

QByteArray SourceStandardRSS::toByteArray() const
{
    return m_url.toString().toUtf8();
}

bool SourceStandardRSS::fromByteArray(const QByteArray &bytes)
{
    if (bytes.isEmpty()) return false;
    
    QUrl urlBuffer{bytes};
    
    if (!urlBuffer.isValid()) return false;
    
    m_url = std::move(urlBuffer);
    
    return true;
}

bool SourceStandardRSS::isValid() const
{
    return m_url.isValid();
}

bool SourceStandardRSS::isPrepared() const
{
    return isValid();
}
