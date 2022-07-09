#ifndef FORMDATA_H
#define FORMDATA_H

#include <QVector>
#include <QVariant>

class FormData
{
    using FormDataElement = std::pair<QString, QVariant>;
    
public:
    FormData();
    
    void addData(const QString &name,
                 const QVariant &data);
    const QVector<FormDataElement>& getData() const;
    
private:
    QVector<FormDataElement> m_data;
};

Q_DECLARE_METATYPE(FormData)

#endif // FORMDATA_H
