/*
** src/board_painter.cpp
*/

#include "board.h"
#include "board_geometry.h"
#include "board_painter.h"
#include "palette.h"

#include <QDebug>

typedef BoardGeometry::Size Size;

BoardPainter::BoardPainter(Board* board)
    : QPainter((QPaintDevice*) board)
{
    m_geo = getBoardGeometry();

    m_pen_line_min = QPen(QBrush(Black), Size::LineMinorWidth);
    m_pen_line_maj = QPen(QBrush(Black), Size::LineMajorWidth);

    m_pen_text = QPen(Blue);
    m_pen_text_given = QPen(Black);

    m_font_number.setPixelSize(Size::NumberSize);
    m_font_mark.setPixelSize(Size::MarkSize);
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

void BoardPainter::paintCellMarks(int row, int col, const Cell& cell)
{
    // givens should never have marks
    if (cell.isGiven())
    {
        return;
    }

    std::array<int8_t, 4> buf;

    //
    // paint center marks
    //

    cell.centerMarks(buf);
    // put marks into a single QString
    QString center_str;
    for (const auto& n : buf)
    {
        if (n >= 0)
        {
            center_str += QString::number(n);
        }
    }
    setPen(m_pen_text);
    drawText(m_geo->cellRect(row, col), Qt::AlignCenter, center_str);

    //
    // paint corner marks
    //

    cell.cornerMarks(buf);
    setPen(m_pen_text);
    for (auto i = 0; i < 4; i++)
    {
        if (buf[i] < 0)
        {
            break;
        }
        auto str = QString::number(buf[i]);
        auto irow = 2 * (i / 2);
        auto icol = 2 * (i % 2);

        drawText(m_geo->cellInnerRect(row, col, irow, icol), Qt::AlignCenter, str);
    }
}

void BoardPainter::paintCell(int row, int col, const Cell& cell)
{
    auto cell_rect = m_geo->cellRect(row, col);

    // highlight cell
    if (cell.isSelected())
    {
        fillRect(cell_rect, Yellow);
    }

    // draw cell number if set
    if (cell.value() >= 0)
    {
        setFont(m_font_number);
        setPen(cell.isGiven() ? m_pen_text_given : m_pen_text);
        drawText(cell_rect, Qt::AlignCenter, QString::number(cell.value()));
    }
    // otherwise, draw marks
    else
    {
        paintCellMarks(row, col, cell);
    }
}

void BoardPainter::paintCells()
{
    auto board = (Board*) device();

    for (auto row = 0; row < 9; row++)
    {
        for (auto col = 0; col < 9; col++)
        {
            paintCell(row, col, board->cell(row, col));
        }
    }
}
