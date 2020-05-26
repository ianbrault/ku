/*
** src/board.cpp
*/

#include "board.h"
#include "palette.h"

#include <QPainter>

Board::Board(QWidget *parent)
    : QWidget(parent)
{
    m_pen_min       = QPen(QBrush(Gray),  LineMinorWidth);
    m_pen_maj_outer = QPen(QBrush(Black), LineMajorWidth);
    m_pen_maj_inner = QPen(QBrush(Gray),  LineMajorWidth);

    setFixedSize(BoardSize, BoardSize);
}

Board::~Board() {}

void Board::paintGridLines(QPainter& painter)
{
    // draw the minor lines
    painter.setPen(m_pen_min);

    for (auto i = 0; i < 3; i++)
    {
        auto majOff = (i + 1) * LineMajorWidth;
        auto off1 = majOff + ((i + 0) * LineMinorWidth) + (((i * 3) + 1) * CellSize);
        auto off2 = majOff + ((i + 1) * LineMinorWidth) + (((i * 3) + 2) * CellSize);

        painter.drawLine(off1, 0, off1, BoardSize);
        painter.drawLine(off2, 0, off2, BoardSize);
        painter.drawLine(0, off1, BoardSize, off1);
        painter.drawLine(0, off2, BoardSize, off2);
    }

    // draw the inside major lines
    painter.setPen(m_pen_maj_inner);

    auto offset = LineMajorWidth + (2 * LineMinorWidth) + (3 * CellSize);
    for (auto i = 1; i < 3; i++)
    {
        auto p = (offset * i) + LineMajorOffset;
        painter.drawLine(p, 0, p, BoardSize);
        painter.drawLine(0, p, BoardSize, p);
    }

    // draw the outside major lines (counter-clockwise)
    painter.setPen(m_pen_maj_outer);

    painter.drawLine(LineMajorOffset, 0, LineMajorOffset, BoardSize);
    painter.drawLine(0, BoardSize - LineMajorOffset, BoardSize, BoardSize - LineMajorOffset);
    painter.drawLine(BoardSize - LineMajorOffset, BoardSize, BoardSize - LineMajorOffset, 0);
    painter.drawLine(BoardSize, LineMajorOffset, 0, LineMajorOffset);
}

void Board::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    paintGridLines(painter);
}
