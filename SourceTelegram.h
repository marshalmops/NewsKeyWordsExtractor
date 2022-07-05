#ifndef SOURCETELEGRAM_H
#define SOURCETELEGRAM_H

#include "SourceBase.h"
#include "AppContext.h"

#include "SourceContextTelegram.h"

class SourceTelegram : public SourceBase
{
public:
    SourceTelegram();
    SourceTelegram(const QString &channelName,
                   const std::shared_ptr<SourceContextTelegram> &sourceContext);
    
    const QString& getChannelName() const;
    AppContext::Id getChannelId  () const;
    
    bool setChannelId(const AppContext::Id channelId);
    
    QByteArray toByteArray  ()                  const override;
    bool       fromByteArray(const QByteArray &bytes) override;
    
    virtual bool isValid   () const override;
    virtual bool isPrepared() const override;
    
protected:
    QString        m_channelName;
    AppContext::Id m_channelId;
};

#endif // SOURCETELEGRAM_H
