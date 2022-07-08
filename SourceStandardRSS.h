#ifndef SOURCESTANDARDRSS_H
#define SOURCESTANDARDRSS_H

#include "SourceBase.h"

class SourceStandardRSS : public SourceBase
{
public:
    SourceStandardRSS();
    SourceStandardRSS(const QUrl &url,
                      const AppContext::Id id = 0);
    
    QByteArray toByteArray  ()                  const override;
    bool       fromByteArray(const QByteArray &bytes) override;
    
    virtual bool isValid   () const override;
    virtual bool isPrepared() const override;
};

#endif // SOURCESTANDARDRSS_H
