#include <QApplication>

#include "AppInitializer.h"

#include "MainCore.h"
#include "NetworkCore.h"
#include "FileManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AppView appView;
    
    std::unique_ptr<MainCore>    mainCore{};
    std::unique_ptr<NetworkCore> networkCore{};
    std::shared_ptr<FileManager> fileManager{};
    
    qRegisterMetaType<Error>();
    qRegisterMetaType<RawNewsDataBase>();
    qRegisterMetaType<FormTemplate>();
    qRegisterMetaType<FormData>();
    
    if (!AppInitializer::initializeApp(app, appView, mainCore, networkCore, fileManager)) { 
        QMessageBox::critical(&appView, QObject::tr("Error"), QObject::tr("Initialization error!"));
        
        return -1;
    }
    
    appView.show();
    
    return app.exec();
}
