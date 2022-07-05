#include "SourceTelegram.h"

SourceTelegram::SourceTelegram()
    : SourceBase{},
      m_channelName{},
      m_channelId{0}
{
    
}

SourceTelegram::SourceTelegram(const QString &channelName,
                               const std::shared_ptr<SourceContextTelegram> &sourceContext)
    : SourceBase{QString{SourceContextTelegram::C_TELEGRAM_API_URL}, sourceContext},
      m_channelName{channelName},
      m_channelId{0}
{
    
}

const QString &SourceTelegram::getChannelName() const
{
    return m_channelName;
}

bool SourceTelegram::setChannelId(const AppContext::Id channelId)
{
    if (channelId <= 0 || m_channelId > 0) return false;
    
    m_channelId = channelId;
    
    return true;
}

QByteArray SourceTelegram::toByteArray() const
{
    return m_url.toString().toUtf8() + SourceBase::C_PARAMS_SEPARATOR 
         + m_channelName.toUtf8() + SourceBase::C_PARAMS_SEPARATOR 
         + QByteArray::number(m_channelId);
}

bool SourceTelegram::fromByteArray(const QByteArray &bytes)
{
    if (bytes.isEmpty()) return false;
    
    size_t curIndex{0};
    
    QByteArray urlBytes{};
    
    if (!getBytesUntil(bytes, curIndex, urlBytes)) return false;
    
    QByteArray channelNameBytes{};
    
    if (!getBytesUntil(bytes, curIndex, channelNameBytes)) return false;
    
    QByteArray channelIdBytes{bytes.mid(curIndex)};
    
    QUrl    urlBuffer        {urlBytes};
    QString channelNameBuffer{channelNameBytes};
    
    bool              isConvOK       {false};
    AppContext::Id    channelIdBuffer{channelIdBytes.toULongLong(&isConvOK)};
    
    if (!urlBuffer.isValid() || channelNameBuffer.isEmpty() || (!channelIdBytes.isEmpty() && !isConvOK))
        return false;
    
    m_url         = std::move(urlBuffer);
    m_channelName = std::move(channelNameBuffer);
    
    if (!channelIdBytes.isEmpty()) m_channelId = channelIdBuffer;
    
    return true;
}

bool SourceTelegram::isValid() const
{
    return (m_url.isValid() && !m_channelName.isEmpty());
}

bool SourceTelegram::isPrepared() const
{
    return (isValid() && m_channelId > 0);
}
