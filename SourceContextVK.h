#ifndef SOURCECONTEXTVK_H
#define SOURCECONTEXTVK_H

#include "SourceContextInterface.h"

#include "AppContext.h"

class SourceContextVK : public SourceContextInterface
{
public:
    constexpr static const char* C_VK_API_URL       = "https://api.vk.com/method/newsfeed.get";
    constexpr static const char* C_TOKEN_PROPERTY   = "token";
    constexpr static const char* C_VERSION_PROPERTY = "V";
    constexpr static const float C_VK_API_VERSION   = 5.131;
    
    SourceContextVK(const AppContext::Token &token = AppContext::Token{});
    
    const AppContext::Token& getToken() const;
    
    virtual AppContext::SourceType getType() const override;
    
    virtual QByteArray toByteArray  ()                  const override;
    virtual bool       fromByteArray(const QByteArray &bytes) override;
    
    virtual bool isPrepared() const override;
    
private:
    AppContext::Token m_token;
};

#endif // SOURCECONTEXTVK_H
