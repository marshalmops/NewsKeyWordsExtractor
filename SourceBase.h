#ifndef SOURCEBASE_H
#define SOURCEBASE_H

#include <QUrl>
#include <memory>

#include "SourceContextInterface.h"
#include "ConvertableToBytes.h"

class SourceBase : public ConvertableToBytes
{
public:
    SourceBase();
    SourceBase(const QUrl &url, 
               const std::shared_ptr<SourceContextInterface> &sourceContext = std::shared_ptr<SourceContextInterface>{nullptr});
    virtual ~SourceBase() = default;
    
    virtual QUrl getBaseUrl() const;
    
    std::shared_ptr<SourceContextInterface> getContext() const;
    bool setContext(const std::shared_ptr<SourceContextInterface> &context);
    
    virtual bool isValid   () const = 0;
    virtual bool isPrepared() const = 0;
    
protected:
    QUrl m_url;
    std::shared_ptr<SourceContextInterface> m_sourceContext;
};

#endif // SOURCEBASE_H
