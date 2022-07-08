#include "FormTemplate.h"

FormTemplate::FormTemplate()
    : m_template{}
{
    
}

void FormTemplate::addParam(const QString &name,
                            const QMetaType::Type type)
{
    m_template.append(TemplateParam{name, type});
}

const QVector<FormTemplate::TemplateParam> &FormTemplate::getTemplateData() const
{
    return m_template;
}
