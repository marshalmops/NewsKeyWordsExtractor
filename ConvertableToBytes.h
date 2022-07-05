#ifndef CONVERTABLETOBYTES_H
#define CONVERTABLETOBYTES_H

#include <QByteArray>

class ConvertableToBytes
{
protected:
    constexpr static const char C_PARAMS_SEPARATOR = ';';
    
public:
    ConvertableToBytes         () = default;
    virtual ~ConvertableToBytes() = default;
    
    virtual QByteArray toByteArray  ()                  const = 0;
    virtual bool       fromByteArray(const QByteArray &bytes) = 0;
    
protected:
    bool getBytesUntil(const QByteArray &bytes,
                       size_t &curIndex,
                       QByteArray &buffer);
};

#endif // CONVERTABLETOBYTES_H
