#include "AppContext.h"

bool AppContext::isPhone(const QString &phone) {
    return (QRegExp{"^\\+[0-9]{1,}$"}.indexIn(phone));
}
