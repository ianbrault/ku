/*
** src/main.cpp
*/

#include "main_window.h"
#ifdef Q_OS_MACOS
#include "osx_manager.h"
#endif

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

#ifdef Q_OS_MACOS
    // make the titlebar transparent on OS X
    OSXManager::removeTitlebarFromWindow();
#endif

    return a.exec();
}
