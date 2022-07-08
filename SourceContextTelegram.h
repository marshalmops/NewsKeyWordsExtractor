#ifndef SOURCECONTEXTTELEGRAM_H
#define SOURCECONTEXTTELEGRAM_H

#include "SourceContextInterface.h"

#include "AppContext.h"

class SourceContextTelegram : public SourceContextInterface
{
public:
    constexpr static const char* C_TELEGRAM_API_URL    = "https://api.telegram.org/bot%1/channels.getMessages";
    constexpr static const char* C_CHANNEL_ID_PROPERTY = "channel";
    
    SourceContextTelegram(const AppContext::Id apiId = 0,
                          const AppContext::Token &apiHash = AppContext::Token{},
                          const AppContext::Phone &phone = AppContext::Phone{});
    
    AppContext::Id           getApiId  () const;
    const AppContext::Token& getApiHash() const;
    const AppContext::Phone& getPhone  () const;
    
    virtual QByteArray toByteArray  ()                  const override;
    virtual bool       fromByteArray(const QByteArray &bytes) override;
    
    virtual bool isPrepared() const override;
    
private:
    AppContext::Id    m_apiId;
    AppContext::Token m_apiHash;
    AppContext::Phone m_phone;
};

#endif // SOURCECONTEXTTELEGRAM_H
