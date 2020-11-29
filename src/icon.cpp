/*
** src/icon_label.cpp
*/

#include "icon.h"
#include "styles.h"

#include <QIcon>

Icon::Icon(QString icon_path, int icon_size, QWidget* parent)
    : QLabel(parent)
{
    // generate icon pixmap
    // scale provided size to the device
    auto size = QSize(icon_size * DevicePixelRatio, icon_size * DevicePixelRatio);
    auto icon_pxm = QIcon(icon_path).pixmap(size);
    icon_pxm.setDevicePixelRatio(DevicePixelRatio);

    setPixmap(icon_pxm);
}

Icon::~Icon() {}
