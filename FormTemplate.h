#ifndef FORMTEMPLATE_H
#define FORMTEMPLATE_H

#include <QVector>
#include <QMetaType>

class FormTemplate
{
    using TemplateParam = std::pair<QString, QMetaType::Type>;
    
public:
    FormTemplate();
    
    void addParam(const QString &name,
                  const QMetaType::Type type);
    
    const QVector<TemplateParam>& getTemplateData() const;
    
private:
    QVector<TemplateParam> m_template;
};

#endif // FORMTEMPLATE_H
