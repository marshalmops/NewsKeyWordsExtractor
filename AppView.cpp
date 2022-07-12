#include "AppView.h"

AppView::AppView(QWidget *parent)
    : QDialog{parent},
      m_isPrepared{false}
{
    QLabel *telegramContextSettingLabel = new QLabel{tr("Telegram setting")};
    
    m_setTelegramContextButton = new QPushButton{tr("Set..")};
    
    QHBoxLayout *telegramContextSettingLayout = new QHBoxLayout{};
    
    telegramContextSettingLayout->addWidget(telegramContextSettingLabel);
    telegramContextSettingLayout->addWidget(m_setTelegramContextButton);
    
    QLabel *vkContextSettingLabel = new QLabel{tr("VK context setting")};
    
    m_setVKContextButton = new QPushButton{tr("Set..")};
    
    QHBoxLayout *vkContextSettingLayout = new QHBoxLayout{};
    
    vkContextSettingLayout->addWidget(vkContextSettingLabel);
    vkContextSettingLayout->addWidget(m_setVKContextButton);
    
    QVBoxLayout *contextSettingLayout = new QVBoxLayout{};
    
    contextSettingLayout->addLayout(telegramContextSettingLayout);
    contextSettingLayout->addLayout(vkContextSettingLayout);
    
    QGroupBox *contextSettingBox = new QGroupBox{tr("Contexts setting")};
    
    contextSettingBox->setLayout(contextSettingLayout);
    
    m_addRSSSourceButton = new QPushButton{tr("Add RSS..")};
    m_removeRSSSourceButton = new QPushButton{tr("Remove RSS")};
    
    QHBoxLayout *rssSourcesButtonsLayout = new QHBoxLayout{};
    
    rssSourcesButtonsLayout->addWidget(m_addRSSSourceButton);
    rssSourcesButtonsLayout->addWidget(m_removeRSSSourceButton);
            
    m_rssSourcesList = new SourceListWidget{new SourceListModelRSS{}};
    
    QVBoxLayout *rssSourcesLayout = new QVBoxLayout{};
    
    rssSourcesLayout->addWidget(m_rssSourcesList);
    rssSourcesLayout->addLayout(rssSourcesButtonsLayout);
    
    m_addTelegramSourceButton = new QPushButton{tr("Add TG channel..")};
    m_removeTelegramSourceButton = new QPushButton{tr("Remove TG channel")};
    
    QHBoxLayout *telegramSourcesButtonsLayout = new QHBoxLayout{};
    
    telegramSourcesButtonsLayout->addWidget(m_addTelegramSourceButton);
    telegramSourcesButtonsLayout->addWidget(m_removeTelegramSourceButton);
            
    m_telegramSourcesList = new SourceListWidget{new SourceListModelTelegram{}};
    
    QVBoxLayout *telegramSourcesLayout = new QVBoxLayout{};
    
    telegramSourcesLayout->addWidget(m_telegramSourcesList);
    telegramSourcesLayout->addLayout(telegramSourcesButtonsLayout);
    
    QHBoxLayout *sourcesLayout = new QHBoxLayout{};
    
    sourcesLayout->addLayout(rssSourcesLayout);
    sourcesLayout->addLayout(telegramSourcesLayout);
    
    QGroupBox *sourcesBox = new QGroupBox{tr("Sources setting")};
    
    sourcesBox->setLayout(sourcesLayout);
    
    m_preparingButton = new QPushButton{tr("Prepare")};
    m_gettingButton   = new QPushButton{tr("Get data")};
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout{};
    
    buttonsLayout->addWidget(m_preparingButton);
    buttonsLayout->addWidget(m_gettingButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{};
    
    mainLayout->addWidget(contextSettingBox);
    mainLayout->addWidget(sourcesBox);
    mainLayout->addLayout(buttonsLayout);
    
    setLayout(mainLayout);
    setWindowTitle(tr("News key words extractor"));
    
    connect(m_setTelegramContextButton,   &QPushButton::clicked, this, &AppView::setTelegramData);
    connect(m_setVKContextButton,         &QPushButton::clicked, this, &AppView::setVKData);
    connect(m_addRSSSourceButton,         &QPushButton::clicked, this, &AppView::addRSSSource);
    connect(m_addTelegramSourceButton,    &QPushButton::clicked, this, &AppView::addTelegramSource);
    connect(m_removeRSSSourceButton,      &QPushButton::clicked, this, &AppView::deleteRSSSource);
    connect(m_removeTelegramSourceButton, &QPushButton::clicked, this, &AppView::deleteTelegramSource);
    connect(m_preparingButton,            &QPushButton::clicked, this, &AppView::prepareContext);
    connect(m_gettingButton,              &QPushButton::clicked, this, &AppView::startDataGetting);    
    
    m_gettingButton->setEnabled(false);
    
    m_addTelegramSourceButton->setEnabled(false);
    m_removeTelegramSourceButton->setEnabled(false);
    
    // FIXME: telegram blocking:
    
    m_isTelegramAllowed = false;
    m_setTelegramContextButton->setEnabled(m_isTelegramAllowed);
}

void AppView::addRSSSource()
{
    FormData     formData{};
    FormTemplate formTemplate{};
    
    formTemplate.addParam("URL", QMetaType::Type::QUrl);
    formTemplate.addParam("Article text class name", QMetaType::Type::QString);
    
    if (!getFormDataWithTemplate(formTemplate, formData)) return;
    
    auto url                  = formData.getData().at(0).second.toUrl();
    auto articleTextClassName = formData.getData().at(1).second.toString();
    
    if (!url.isValid() || articleTextClassName.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Provided data is incorrect!"));
        
        return;
    }
    
    changeLoadingState(true);
    
    emit rssSourceAdded(url.toString(), articleTextClassName);
}

void AppView::addTelegramSource()
{
    FormData     formData{};
    FormTemplate formTemplate{};
    
    formTemplate.addParam("Channel name", QMetaType::Type::QString);
    
    if (!getFormDataWithTemplate(formTemplate, formData)) return;
    
    auto channelName = formData.getData().at(0).second.toString();
    
    if (channelName.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Provided data is incorrect!"));
        
        return;
    }
    
    changeLoadingState(true);
    
    emit telegramSourceAdded(channelName);
}

void AppView::deleteRSSSource()
{
    if (!m_rssSourcesList->currentIndex().isValid()) {
        QMessageBox::warning(this, tr("Error"), tr("Choose the source to delete!"));
        
        return;
    }
    
    changeLoadingState(true);
    
    emit rssSourceDeleted(m_rssSourcesList->getLastSelectedSourceId());
}

void AppView::deleteTelegramSource()
{
    if (!m_rssSourcesList->currentIndex().isValid()) {
        QMessageBox::warning(this, tr("Error"), tr("Choose the source to delete!"));
        
        return;
    }
    
    changeLoadingState(true);
    
    emit rssSourceDeleted(m_telegramSourcesList->getLastSelectedSourceId());
}

void AppView::insertRSSSourceRow()
{
    if (!m_rssSourcesList->insertSourceRow()) {
        emit errorOccured(Error{"RSS Sources view updating error!", true});
        
        return;
    }
    
    changeLoadingState(false);
}

void AppView::insertTelegramSourceRow()
{
    if (!m_telegramSourcesList->insertSourceRow()) {
        emit errorOccured(Error{"Telegram Sources view updating error!", true});
        
        return;
    }
    
    changeLoadingState(false);
}

void AppView::deleteRSSSourceRow()
{
    if (!m_rssSourcesList->removeLastSelectedSourceRow()) {
        emit errorOccured(Error{"RSS Sources view updating error!", true});
        
        return;
    }
    
    changeLoadingState(false);
}

void AppView::deleteTelegramSourceRow()
{
    if (!m_telegramSourcesList->removeLastSelectedSourceRow()) {
        emit errorOccured(Error{"Telegram Sources view updating error!", true});
        
        return;
    }
    
    changeLoadingState(false);
}

void AppView::setVKData()
{
    FormData     formData{};
    FormTemplate formTemplate{};
    
    formTemplate.addParam("Token", QMetaType::Type::QString);
    
    if (!getFormDataWithTemplate(formTemplate, formData)) return;
    
    auto token = formData.getData().at(0).second.toString();
    
    if (token.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Provided data is incorrect!"));
        
        return;
    }
    
    emit vkDataProvided(token);
}

void AppView::setTelegramData()
{
    FormData     formData{};
    FormTemplate formTemplate{};
    
    formTemplate.addParam("Phone",    QMetaType::Type::QString);
    formTemplate.addParam("API Id",   QMetaType::Type::ULongLong);
    formTemplate.addParam("API Hash", QMetaType::Type::QString);
    
    if (!getFormDataWithTemplate(formTemplate, formData)) return;
    
    bool isApiIdConvOK{false};
    
    auto phone   = formData.getData().at(0).second.toString();
    auto apiId   = formData.getData().at(1).second.toULongLong(&isApiIdConvOK);
    auto apiHash = formData.getData().at(2).second.toString();
    
    if (phone.isEmpty() || !isApiIdConvOK || apiHash.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Provided data is incorrect!"));
        
        return;
    }
    
    emit telegramDataProvided(phone, apiId, apiHash);
}

void AppView::getFormDataByTemplate(const FormTemplate paramsToGet)
{
    FormData formData{};
    
    if (!getFormDataWithTemplate(paramsToGet, formData)) return;
    
    emit formDataGot(formData);
}

void AppView::startContextPreparing()
{
    changeLoadingState(true);
    
    emit prepareContext();
}

void AppView::endContextPreparing()
{
    m_isPrepared = true;
    
    changeLoadingState(false);
    m_gettingButton->setEnabled(true);
}

void AppView::startDataGetting()
{
    changeLoadingState(true);
    
    emit getData();
}

void AppView::endDataGetting()
{
    QMessageBox::information(this, tr("Success"), tr("Provided data has been processed!"));
    
    changeLoadingState(false);
}

bool AppView::getFormDataWithTemplate(const FormTemplate &formTemplate,
                                      FormData &formData)
{
    switch (FormWidget{formTemplate, formData}.exec()) {
    case QDialog::Rejected: return false;
    case FormWidget::C_ERROR_OCCURED: {
        QMessageBox::warning(this, tr("Error"), tr("Provided data is incorrect!"));
        
        return false;
    }
    }
    
    if (formData.getData().length() != formTemplate.getTemplateData().length()) {
        QMessageBox::warning(this, tr("Error"), tr("Provided data is not full!"));
        
        return false;
    }
    
    return true;
}

void AppView::changeLoadingState(bool isLoading)
{
    // elements enabling changing...
    
    m_setTelegramContextButton->setEnabled(!isLoading && m_isTelegramAllowed);
    m_setVKContextButton->setEnabled(!isLoading);
    m_addRSSSourceButton->setEnabled(!isLoading);
    m_removeRSSSourceButton->setEnabled(!isLoading);
    m_addTelegramSourceButton->setEnabled(!isLoading && m_isTelegramAllowed);
    m_removeTelegramSourceButton->setEnabled(!isLoading && m_isTelegramAllowed);
    m_preparingButton->setEnabled(!isLoading);
    m_gettingButton->setEnabled(!isLoading && m_isPrepared);
}
