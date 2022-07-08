#ifndef SOURCECONTEXTINTERFACE_H
#define SOURCECONTEXTINTERFACE_H

#include <QByteArray>

#include "AppContext.h"

#include "ConvertableToBytes.h"
#include "PreparableObject.h"

class SourceContextInterface
        : public ConvertableToBytes,
          public PreparableObject
{
protected:
    constexpr static const char C_PARAMS_SEPARATOR = ';';
    
public:   
    SourceContextInterface         () = default;
    virtual ~SourceContextInterface() = default;
    
    virtual AppContext::SourceType getType() const = 0;
    
    virtual bool isPrepared() const = 0;
};

#endif // SOURCECONTEXTINTERFACE_H
