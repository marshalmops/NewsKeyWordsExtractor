#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include "AppView.h"

class AppInitializer
{
public:
    AppInitializer() = delete;
    
    static bool initializeApp(AppView &appView);
};

#endif // APPINITIALIZER_H
