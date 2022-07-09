#ifndef APPVIEW_H
#define APPVIEW_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QUrl>
#include <QGroupBox>

#include "AppContext.h"

#include "Error.h"

#include "FormWidget.h"
#include "FormData.h"
#include "FormTemplate.h"

#include "SourceListWidget.h"
#include "SourceListModelRSS.h"
#include "SourceListModelTelegram.h"

class AppView : public QDialog
{
    Q_OBJECT
public:
    explicit AppView(QWidget *parent = nullptr);
    
signals:
    // to MainCore:
    
    void errorOccured(const Error err);
    
    void rssSourceAdded     (const QString rssSource);
    void telegramSourceAdded(const QString telegramSource);
    
    void rssSourceDeleted     (const AppContext::Id id);
    void telegramSourceDeleted(const AppContext::Id id);
    
    void vkDataProvided      (const AppContext::Token token);
    void telegramDataProvided(const AppContext::Phone phone,
                              const AppContext::Id apiId,
                              const AppContext::Token apiHash);
    
    void prepareContext();
    void getData();
    
    void formDataGot(const FormData formData);
    
public slots:
    void addRSSSource     ();
    void addTelegramSource();
    
    void deleteRSSSource     ();
    void deleteTelegramSource();
    
    void insertRSSSourceRow     ();
    void insertTelegramSourceRow();
    
    void deleteRSSSourceRow     ();
    void deleteTelegramSourceRow();
    
    void setVKData      ();
    void setTelegramData();
    
    void getFormDataByTemplate(const FormTemplate paramsToGet);
    
    void startContextPreparing();
    void endContextPreparing  ();
    
    void startDataGetting();
    void endDataGetting();
    
private:
    bool getFormDataWithTemplate(const FormTemplate &formTemplate,
                                 FormData &formData);
    void changeLoadingState(bool isLoading = false);
    
private:
    SourceListWidget *m_rssSourcesList;
    SourceListWidget *m_telegramSourcesList;
    
    QPushButton *m_setTelegramContextButton;
    QPushButton *m_setVKContextButton;
    
    QPushButton *m_addRSSSourceButton;
    QPushButton *m_removeRSSSourceButton;
    
    QPushButton *m_addTelegramSourceButton;
    QPushButton *m_removeTelegramSourceButton;
    
    QPushButton *m_preparingButton;
    QPushButton *m_gettingButton;
    
    bool m_isPrepared;
    
    bool m_isTelegramAllowed;
};

#endif // APPVIEW_H
