#ifndef FORMWIDGET_H
#define FORMWIDGET_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegularExpressionValidator>
#include <QUrl>

#include "FormTemplate.h"
#include "FormData.h"

class FormWidget : public QDialog
{
    Q_OBJECT
public:
    explicit FormWidget(const FormTemplate &formTemplate,
                        FormData &formData,
                        QWidget *parent = nullptr);
    
public slots:
    void accept();
    
private:
    QLineEdit* generateInputWidgetByMetaType(const QMetaType::Type type);
    QVariant   generateVariantofStringByMetaType(const QString &str,
                                                 const QMetaType::Type type);
    
private:
    const FormTemplate &m_template;
    FormData           &m_data;
    
    QVector<QLineEdit*> m_inputs;
};

#endif // FORMWIDGET_H
