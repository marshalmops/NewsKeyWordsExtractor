#include "SourceStandardRSS.h"

SourceStandardRSS::SourceStandardRSS()
    : SourceBase{}
{
    
}

SourceStandardRSS::SourceStandardRSS(const QUrl &url, 
                                     const QString &articleTextClassName, 
                                     const AppContext::Id id)
    : SourceBase{url, id},
      m_articleTextClassName{articleTextClassName}
{
    
}

AppContext::SourceType SourceStandardRSS::getType() const
{
    return AppContext::SourceType::ST_STANDARD_RSS;
}

QString SourceStandardRSS::getArticleTextClassName() const
{
    return m_articleTextClassName;
}

QByteArray SourceStandardRSS::toByteArray() const
{
    return m_url.toString().toUtf8() + ConvertableToBytes::C_PARAMS_SEPARATOR
         + m_articleTextClassName.toUtf8();
}

bool SourceStandardRSS::fromByteArray(const QByteArray &bytes)
{
    if (bytes.isEmpty()) return false;
    
    size_t curIndex{0};
    QByteArray urlBytes{};
    
    if (!getBytesUntil(bytes, curIndex, urlBytes)) return false;
    
    QByteArray articleTextClassNameBytes{bytes.mid(curIndex)};
    
    QUrl    urlBuffer{urlBytes};
    QString articleTextClassNameBuffer{articleTextClassNameBytes};
    
    if (!urlBuffer.isValid() || articleTextClassNameBuffer.length() <= 0) return false;
    
    m_url                  = std::move(urlBuffer);
    m_articleTextClassName = std::move(articleTextClassNameBuffer);
    
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
