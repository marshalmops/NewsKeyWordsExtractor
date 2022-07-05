#include "Error.h"

Error::Error(const QString &text, 
             bool isCritical)
    : m_text{text},
      m_isCritical{isCritical}
{
    
}

const QString &Error::getText() const
{
    return m_text;
}

bool Error::isCritical() const
{
    return m_isCritical;
}
