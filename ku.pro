# ku.pro

QT      += core gui widgets
CONFIG  += c++17
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    src/board/board.h \
    src/board/board_geometry.h \
    src/board/board_painter.h \
    src/board/board_types.h \
    src/board/cell.h \
    src/input_mode_selector.h \
    src/main_view.h \
    src/main_window.h \
    src/palette.h

SOURCES += \
    src/board/board.cpp \
    src/board/board_geometry.cpp \
    src/board/board_painter.cpp \
    src/board/cell.cpp \
    src/input_mode_selector.cpp \
    src/main.cpp \
    src/main_view.cpp \
    src/main_window.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
