#include "ConvertableToBytes.h"

bool ConvertableToBytes::getBytesUntil(const QByteArray &bytes,
                               size_t &curIndex,
                               QByteArray &buffer)
{
    while (true) {
        if (bytes.at(curIndex) == ConvertableToBytes::C_PARAMS_SEPARATOR) {
            ++curIndex;
            
            break;
        }
        
        buffer   += bytes.at(curIndex);
        curIndex += 1;
        
        if (curIndex >= bytes.length()) return false;
    }
    
    return true;
}

