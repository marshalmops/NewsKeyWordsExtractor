#ifndef SOURCEBASE_H
#define SOURCEBASE_H

#include "AppContext.h"

#include <QUrl>
#include <memory>

#include "SourceContextInterface.h"
#include "ConvertableToBytes.h"
#include "PreparableObject.h"

class SourceBase
        : public ConvertableToBytes,
          public PreparableObject
{
public:
    SourceBase();
    SourceBase(const QUrl &url, 
               const AppContext::Id id = 0,
               const std::shared_ptr<SourceContextInterface> &sourceContext = std::shared_ptr<SourceContextInterface>{nullptr});
    virtual ~SourceBase() = default;
    
    virtual QUrl getBaseUrl() const;
    
    std::shared_ptr<SourceContextInterface> getContext() const;
    bool setContext(const std::shared_ptr<SourceContextInterface> &context);
    
    AppContext::Id getId() const;
    bool setId(const AppContext::Id id);
    
    virtual bool isValid   () const = 0;
    virtual bool isPrepared() const = 0;
    
protected:
    QUrl m_url;
    std::shared_ptr<SourceContextInterface> m_sourceContext;
    
    AppContext::Id m_id;
};

#endif // SOURCEBASE_H
