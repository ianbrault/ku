# ku.pro

QT      += core gui widgets
CONFIG  += c++17
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    src/board.h \
    src/board_painter.h \
    src/cell.h \
    src/main_view.h \
    src/main_window.h \
    src/palette.h

SOURCES += \
    src/board.cpp \
    src/board_painter.cpp \
    src/cell.cpp \
    src/main.cpp \
    src/main_view.cpp \
    src/main_window.cpp

macx {
    HEADERS += src/osx_manager.h
    SOURCES += src/osx_manager.mm
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
