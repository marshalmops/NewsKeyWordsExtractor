#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QString>
#include <QRegExp>

namespace AppContext
{

using Token = QString;
using Id    = uint64_t;
using Phone = QString;

using WordsFrequency = uint64_t;

bool isPhone(const QString &phone) {
    return (QRegExp{"^\\+[0-9]{1,}$"}.indexIn(phone));
}

};

#endif // APPCONTEXT_H
