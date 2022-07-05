#include <QApplication>

#include "AppInitializer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppView w;
    
    w.show();
    
    return a.exec();
}
