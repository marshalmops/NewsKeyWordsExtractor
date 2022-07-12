#include "FormWidget.h"

FormWidget::FormWidget(const FormTemplate &formTemplate,
                       FormData &formData,
                       QWidget *parent)
    : QDialog{parent},
      m_template{formTemplate},
      m_data{formData}
{
    QVBoxLayout *labelsLayout = new QVBoxLayout{};
    QVBoxLayout *inputsLayout = new QVBoxLayout{};
    
    foreach (const auto &param, formTemplate.getTemplateData()) {
        QLabel    *newLabel = new QLabel{param.first};
        QLineEdit *newInput = generateInputWidgetByMetaType(param.second);
        
        labelsLayout->addWidget(newLabel);
        inputsLayout->addWidget(newInput);
        
        m_inputs.append(newInput);
    }
    
    QHBoxLayout *formLayout = new QHBoxLayout{};
    
    formLayout->addLayout(labelsLayout);
    formLayout->addLayout(inputsLayout);
    
    QPushButton *acceptButton = new QPushButton{tr("Accept")};
    QPushButton *cancelButton = new QPushButton{tr("Cancel")};
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout{};
    
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(acceptButton);
    buttonsLayout->addWidget(cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{};
    
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonsLayout);
    
    setLayout(mainLayout);
    
    connect(acceptButton, &QPushButton::clicked, this, &FormWidget::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    setWindowTitle(tr("Data request"));
}

void FormWidget::accept()
{
    for (auto i = 0; i < m_template.getTemplateData().length(); ++i) {
        auto rawDataStr   = m_inputs.at(i)->text();
        auto templateItem = m_template.getTemplateData().at(i);
        
        auto curValue = generateVariantofStringByMetaType(rawDataStr, templateItem.second);
    
        if (curValue.isNull()) {
            QDialog::done(-1);
            
            return;
        }
        
        m_data.addData(templateItem.first, curValue);
    }
    
    QDialog::accept();
}

QLineEdit *FormWidget::generateInputWidgetByMetaType(const QMetaType::Type type)
{
    QLineEdit* newInput = new QLineEdit{};
    QRegularExpressionValidator *newValidator;
    
    switch (type) {
    case QMetaType::Type::Double:
    case QMetaType::Type::Float:
    case QMetaType::Type::Int:
    case QMetaType::Type::UInt:
    case QMetaType::Type::Long:
    case QMetaType::Type::LongLong:
    case QMetaType::Type::ULong:
    case QMetaType::Type::ULongLong: {
        newValidator = new QRegularExpressionValidator{QRegularExpression{"[0-9]{0,}"}};
        
        break;
    }
    case QMetaType::Type::QUrl: {
        newValidator = new QRegularExpressionValidator{QRegularExpression{"((http|https|ftp)://|(www)\\.)(\\w+)(\\.?[\\.a-z0-9/:?%&=\\-_+#;]*)"}};
        
        break;
    }
    default: {newValidator = new QRegularExpressionValidator{QRegularExpression{"[A-Za-z]+[\\w-]*"}};
    }
    }
    
    if (newValidator) newInput->setValidator(newValidator);
    
    return newInput;
}

QVariant FormWidget::generateVariantofStringByMetaType(const QString &str,
                                                       const QMetaType::Type type)
{
    switch (type) {
    case QMetaType::Type::Double:    return QVariant{str.toDouble()};
    case QMetaType::Type::Float:     return QVariant{str.toFloat()};
    case QMetaType::Type::Int:       return QVariant{str.toInt()};
    case QMetaType::Type::UInt:      return QVariant{str.toUInt()};
    case QMetaType::Type::Long:
    case QMetaType::Type::LongLong:  return QVariant{str.toLongLong()};
    case QMetaType::Type::ULong:
    case QMetaType::Type::ULongLong: return QVariant{str.toULongLong()};
    case QMetaType::Type::QUrl: {
        if (!QRegularExpression{"((http|https|ftp)://|(www)\\.)(\\w+)(\\.?[\\.a-z0-9/:?%&=\\-_+#;]*)"}.match(str).hasMatch()) return QVariant{};
        
        return QVariant{QUrl{str, QUrl::ParsingMode::StrictMode}};
    }
    default:                         return QVariant{str};
    }
    
    return QVariant{};
}
