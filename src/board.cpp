/*
** src/board.cpp
*/

#include "board.h"
#include "palette.h"

#include <QPainter>

Board::Board(QWidget *parent)
    : QWidget(parent)
{
    m_pen_min = QPen(QBrush(Black), LineMinorWidth);
    m_pen_maj = QPen(QBrush(Black), LineMajorWidth);

    m_font_number.setPixelSize(NumberSize);

    // calculate cell offsets
    auto offset = [](int i, int j) {
        return (i * LineMajorWidth) + (j * CellSize);
    };

    for (auto i = 0; i < 3; i++)
    {
        m_cell_offsets[(i * 3)]     = offset(i + 1, (i * 3));
        m_cell_offsets[(i * 3) + 1] = offset(i + 1, (i * 3) + 1);
        m_cell_offsets[(i * 3) + 2] = offset(i + 1, (i * 3) + 2);
    }

    setFixedSize(BoardSize, BoardSize);
}

Board::~Board() {}

void Board::paintGridLines(QPainter& painter)
{
    // draw the minor lines
    painter.setPen(m_pen_min);

    for (auto i = 1; i < 9; i += 3)
    {
        painter.drawLine(m_cell_offsets[i],     0, m_cell_offsets[i],     BoardSize);
        painter.drawLine(m_cell_offsets[i + 1], 0, m_cell_offsets[i + 1], BoardSize);
        painter.drawLine(0, m_cell_offsets[i],     BoardSize, m_cell_offsets[i]);
        painter.drawLine(0, m_cell_offsets[i + 1], BoardSize, m_cell_offsets[i + 1]);
    }

    // draw the inside major lines
    painter.setPen(m_pen_maj);

    for (auto i = 0; i < 9; i += 3)
    {
        auto p = m_cell_offsets[i] - LineMajorOffset;
        painter.drawLine(p, 0, p, BoardSize);
        painter.drawLine(0, p, BoardSize, p);
    }

    // draw the outside major lines (counter-clockwise)
    painter.drawLine(LineMajorOffset, 0, LineMajorOffset, BoardSize);
    painter.drawLine(0, BoardSize - LineMajorOffset, BoardSize, BoardSize - LineMajorOffset);
    painter.drawLine(BoardSize - LineMajorOffset, BoardSize, BoardSize - LineMajorOffset, 0);
    painter.drawLine(BoardSize, LineMajorOffset, 0, LineMajorOffset);
}

QRect Board::getCellRect(int row, int col) const
{
    return QRect(m_cell_offsets[row], m_cell_offsets[col], CellSize, CellSize);
}

void Board::paintCell(QPainter& painter, int row, int col, const Cell& cell)
{
    auto rect = getCellRect(row, col);

    // draw cell number (if set)
    if (cell.value() >= 0)
    {
        painter.setFont(m_font_number);
        painter.drawText(rect, Qt::AlignCenter, QString::number(cell.value()));
    }
}

void Board::paintCells(QPainter& painter)
{
    for (auto row = 0; row < 9; row++)
    {
        for (auto col = 0; col < 9; col++)
        {
            paintCell(painter, row, col, m_cells[(row * 9) + col]);
        }
    }
}

void Board::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    paintCells(painter);
    paintGridLines(painter);
}
