#include "FormData.h"

FormData::FormData()
    : m_data{}
{
    
}

void FormData::addData(const QString &name, 
                       const QVariant &data)
{
    m_data.append(FormDataElement{name, data});
}

const QVector<FormData::FormDataElement> &FormData::getData() const
{
    return m_data;
}
