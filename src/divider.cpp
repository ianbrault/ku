/*
** src/divider.cpp
*/

#include "divider.h"
#include "styles.h"

#include <QPainter>

static const auto HPadding = 8;
static const auto VPadding = 4;
static const auto LineHeight = 1;

Divider::Divider(QWidget* parent)
    : QWidget(parent)
{
    // grow to fill container width, but set fixed height
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(2 * VPadding + LineHeight);

    m_pen = QPen(QBrush(MediumGray), LineHeight, Qt::SolidLine, Qt::RoundCap);
}

Divider::~Divider() {}


void Divider::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(m_pen);
    painter.drawLine(HPadding, VPadding, width() - HPadding, VPadding);
}
