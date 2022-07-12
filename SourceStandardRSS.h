#ifndef SOURCESTANDARDRSS_H
#define SOURCESTANDARDRSS_H

#include "SourceBase.h"

class SourceStandardRSS : public SourceBase
{
public:
    SourceStandardRSS();
    SourceStandardRSS(const QUrl &url,
                      const QString &articleTextClassName,
                      const AppContext::Id id = 0);
    
    virtual AppContext::SourceType getType() const override;
    
    QString getArticleTextClassName() const;
    
    QByteArray toByteArray  ()                  const override;
    bool       fromByteArray(const QByteArray &bytes) override;
    
    virtual bool isValid   () const override;
    virtual bool isPrepared() const override;
    
private:
    QString m_articleTextClassName;
};

#endif // SOURCESTANDARDRSS_H
