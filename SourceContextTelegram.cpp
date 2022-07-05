#include "SourceContextTelegram.h"

SourceContextTelegram::SourceContextTelegram(const AppContext::Id apiId,
                                             const AppContext::Token &apiHash, 
                                             const AppContext::Phone &phone)
    : m_apiId{apiId},
      m_apiHash{apiHash},
      m_phone{phone}
{
    
}

AppContext::Id SourceContextTelegram::getApiId() const
{
    return m_apiId;
}

const AppContext::Token &SourceContextTelegram::getApiHash() const
{
    return m_apiHash;
}

const AppContext::Phone &SourceContextTelegram::getPhone() const
{
    return m_phone;
}

QByteArray SourceContextTelegram::toByteArray() const
{
    return (QByteArray::number(m_apiId) + C_PARAMS_SEPARATOR
          + m_apiHash.toUtf8() + C_PARAMS_SEPARATOR
          + m_phone.toUtf8());
}

bool SourceContextTelegram::fromByteArray(const QByteArray &bytes)
{
    if (bytes.isEmpty()) return false;
    
    size_t curIndex{0};
    
    QByteArray apiIdBytes{};
    
    if (!getBytesUntil(bytes, curIndex, apiIdBytes)) return false;
    
    QByteArray apiHashBytes{};
    
    if (!getBytesUntil(bytes, curIndex, apiHashBytes)) return false;
    
    QByteArray phone{bytes.mid(curIndex)};
    
    bool isConvOK{false};
    
    AppContext::Id    apiIdBuffer  {apiIdBytes.toULongLong(&isConvOK)};
    AppContext::Token apiHashBuffer{apiHashBytes};
    AppContext::Phone phoneBuffer  {phone};
    
    if (!isConvOK || apiHashBuffer.isEmpty() || !AppContext::isPhone(phoneBuffer))
        return false;
    
    m_apiId   = apiIdBuffer;
    m_apiHash = std::move(apiHashBuffer);
    m_phone   = std::move(phoneBuffer);
    
    return true;
}

bool SourceContextTelegram::isPrepared() const
{
    return (m_apiId > 0 && !m_apiHash.isEmpty() && AppContext::isPhone(m_phone));
}
