#include "SourceContextVK.h"


SourceContextVK::SourceContextVK(const AppContext::Token &token)
    : m_token{token}
{
    
}

const AppContext::Token &SourceContextVK::getToken() const
{
    return m_token;
}

AppContext::SourceType SourceContextVK::getType() const
{
    return AppContext::SourceType::ST_VK;
}

QByteArray SourceContextVK::toByteArray() const
{
    return (m_token.toUtf8());
}

bool SourceContextVK::fromByteArray(const QByteArray &bytes)
{
    if (bytes.isEmpty()) return false;
    
    size_t curIndex{0};
    
    QByteArray tokenBytes{bytes.mid(curIndex)};
    
    AppContext::Token tokenBuffer{tokenBytes};
    
    if (tokenBuffer.isEmpty()) return false;
    
    m_token = std::move(tokenBuffer);
    
    return true;
}

bool SourceContextVK::isPrepared() const
{
    return !m_token.isEmpty();
}
