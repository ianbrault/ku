/*
** src/osx_manager.mm
*/

#include "osx_manager.h"

#include <Cocoa/Cocoa.h>
#include <QGuiApplication>
#include <QWindow>

void OSXManager::removeTitlebarFromWindow(long winId)
{
    if(winId < 0)
    {
        QWindowList windows = QGuiApplication::allWindows();
        QWindow* win = windows.first();
        winId = win->winId();
    }

    NSView *nativeView = reinterpret_cast<NSView *>(winId);
    NSWindow* nativeWindow = [nativeView window];
    nativeWindow.backgroundColor = [NSColor whiteColor];
    [nativeWindow setTitlebarAppearsTransparent:YES];
}
