/*
** src/board_painter.cpp
*/

#include "board.h"
#include "board_geometry.h"
#include "board_painter.h"
#include "palette.h"

typedef BoardGeometry::Size Size;

BoardPainter::BoardPainter(Board* board)
    : QPainter((QPaintDevice*) board)
{
    // FIXME: this should share the same instance with the Board
    m_geo = new BoardGeometry();

    m_pen_line_min = QPen(QBrush(Black), Size::LineMinorWidth);
    m_pen_line_maj = QPen(QBrush(Black), Size::LineMajorWidth);

    m_pen_text = QPen(Blue);
    m_pen_text_given = QPen(Black);

    m_font_number.setPixelSize(Size::NumberSize);
}

BoardPainter::~BoardPainter() {}

void BoardPainter::paint(QPaintEvent*)
{
    // blank the whole board
    fillRect(0, 0, Size::BoardSize, Size::BoardSize, White);

    paintCells();
    paintGridLines();
}

void BoardPainter::paintGridLines()
{
    // draw the minor lines
    setPen(m_pen_line_min);

    for (auto i = 1; i < 9; i += 3)
    {
        drawLine(m_geo->cellOffset(i),   0, m_geo->cellOffset(i),   Size::BoardSize);
        drawLine(m_geo->cellOffset(i+1), 0, m_geo->cellOffset(i+1), Size::BoardSize);
        drawLine(0, m_geo->cellOffset(i),   Size::BoardSize, m_geo->cellOffset(i));
        drawLine(0, m_geo->cellOffset(i+1), Size::BoardSize, m_geo->cellOffset(i+1));
    }

    // draw the inside major lines
    setPen(m_pen_line_maj);

    for (auto i = 0; i < 9; i += 3)
    {
        auto p = m_geo->cellOffset(i) - Size::LineMajorOffset;
        drawLine(p, 0, p, Size::BoardSize);
        drawLine(0, p, Size::BoardSize, p);
    }

    // draw the outside major lines (counter-clockwise)
    drawLine(Size::LineMajorOffset, 0, Size::LineMajorOffset, Size::BoardSize);
    drawLine(0, Size::BoardSize - Size::LineMajorOffset, Size::BoardSize, Size::BoardSize - Size::LineMajorOffset);
    drawLine(Size::BoardSize - Size::LineMajorOffset, Size::BoardSize, Size::BoardSize - Size::LineMajorOffset, 0);
    drawLine(Size::BoardSize, Size::LineMajorOffset, 0, Size::LineMajorOffset);
}

void BoardPainter::paintCell(int row, int col, const Cell& cell)
{
    auto rect = m_geo->cellRect(row, col);

    // highlight cell
    if (cell.isSelected())
        fillRect(rect, Yellow);

    // draw cell number
    if (cell.value() >= 0)
    {
        setFont(m_font_number);
        setPen(cell.isGiven() ? m_pen_text_given : m_pen_text);
        drawText(rect, Qt::AlignCenter, QString::number(cell.value()));
    }
}

void BoardPainter::paintCells()
{
    auto board = (Board*) device();

    for (auto row = 0; row < 9; row++)
        for (auto col = 0; col < 9; col++)
            paintCell(row, col, board->cell(row, col));
}
