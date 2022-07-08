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
    
    if (!AppInitializer::initializeApp(app, appView, mainCore, networkCore, fileManager)) 
        return -1;
    
    appView.show();
    
    return app.exec();
}
