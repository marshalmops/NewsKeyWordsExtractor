#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QString>
#include <QRegExp>

namespace AppContext
{
constexpr static const uint64_t C_TICK_DELAY_MS = 200;

using Token = QString;
using Id    = uint64_t;
using Phone = QString;

using WordsFrequency = uint64_t;

bool isPhone(const QString &phone);

enum SourceType : uint8_t {
    ST_INVALID = 0,
    ST_STANDARD_RSS,
    ST_TELEGRAM,
    ST_VK
};

};

#endif // APPCONTEXT_H
