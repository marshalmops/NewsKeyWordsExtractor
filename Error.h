#ifndef ERROR_H
#define ERROR_H

#include <QString>

class Error
{
public:
    Error(const QString &text,
          bool isCritical = false);
    
    const QString& getText   () const;
    bool           isCritical() const;
    
private:
    QString m_text;
    bool    m_isCritical;
};

#endif // ERROR_H
