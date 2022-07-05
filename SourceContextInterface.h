#ifndef SOURCECONTEXTINTERFACE_H
#define SOURCECONTEXTINTERFACE_H

#include <QByteArray>

#include "ConvertableToBytes.h"

class SourceContextInterface : public ConvertableToBytes
{
protected:
    constexpr static const char C_PARAMS_SEPARATOR = ';';
    
public:   
    SourceContextInterface         () = default;
    virtual ~SourceContextInterface() = default;
    
    virtual bool isPrepared() const = 0;
};

#endif // SOURCECONTEXTINTERFACE_H
