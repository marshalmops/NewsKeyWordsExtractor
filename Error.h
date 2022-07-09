#ifndef ERROR_H
#define ERROR_H

#include <QString>
#include <QMetaType>

class Error
{
public:
    Error() = default;
    Error(const QString &text,
          bool isCritical = false);
    
    const QString& getText   () const;
    bool           isCritical() const;
    
private:
    QString m_text;
    bool    m_isCritical;
};

Q_DECLARE_METATYPE(Error)

#endif // ERROR_H
