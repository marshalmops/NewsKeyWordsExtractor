#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include <QApplication>

#include "AppView.h"

#include "MainCore.h"
#include "NetworkCore.h"
#include "FileManager.h"

class AppInitializer
{
public:
    AppInitializer() = delete;
    
    static bool initializeApp(QApplication &app,
                              AppView &appView,
                              std::unique_ptr<MainCore> &mainCore,
                              std::unique_ptr<NetworkCore> &networkCore,
                              std::shared_ptr<FileManager> &fileManager);
};

#endif // APPINITIALIZER_H
