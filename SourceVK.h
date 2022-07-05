#ifndef SOURCEVK_H
#define SOURCEVK_H

#include "AppContext.h"
#include "SourceBase.h"

#include "SourceContextVK.h"

class SourceVK : public SourceBase
{
public:
    SourceVK();
    SourceVK(const std::shared_ptr<SourceContextVK> &sourceContext);
    
    QByteArray toByteArray  ()                  const override;
    bool       fromByteArray(const QByteArray &bytes) override;
    
    virtual bool isValid   () const override;
    virtual bool isPrepared() const override;
    
protected:
    //AppContext::Token m_token;
};

#endif // SOURCEVK_H
