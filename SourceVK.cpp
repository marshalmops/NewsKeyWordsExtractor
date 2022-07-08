#include "SourceVK.h"

SourceVK::SourceVK(const AppContext::Id id,
                   const std::shared_ptr<SourceContextVK> &sourceContext)
    : SourceBase{QString{SourceContextVK::C_VK_API_URL}, id, sourceContext}
{
    
}

QByteArray SourceVK::toByteArray() const
{
    return m_url.toString().toUtf8();
}

bool SourceVK::fromByteArray(const QByteArray &bytes)
{
    if (bytes.isEmpty()) return false;
    
    size_t curIndex{0};
    
    QByteArray urlBytes{bytes.mid(curIndex)};
    
//    if (!getBytesUntil(bytes, curIndex, urlBytes)) return false;
    
//    QByteArray tokenBytes{bytes.mid(curIndex)};
    
    QUrl              urlBuffer      {urlBytes};
    //AppContext::Token tokenBuffer    {tokenBytes};
    
    if (!urlBuffer.isValid()) return false;
    
    m_url       = std::move(urlBuffer);
    //m_token     = std::move(tokenBuffer);
    
    return true;
}

bool SourceVK::isValid() const
{
    return (m_url.isValid());
}

bool SourceVK::isPrepared() const
{
    return isValid();
}
