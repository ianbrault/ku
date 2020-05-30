/*
** src/board.cpp
*/

#include "board.h"
#include "palette.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

Board::Board(QWidget *parent)
    : QWidget(parent), m_cell_selected(-1)
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
    grabKeyboard();
}

Board::~Board() {}

void Board::selectCell(int row, int col)
{
    auto target = (row * 9) + col;
    m_cells[target].toggleSelect();

    if (target == m_cell_selected)
    {
        m_cell_selected = -1;
    }
    else
    {
        if (m_cell_selected >= 0)
            m_cells[m_cell_selected].toggleSelect();
        m_cell_selected = target;
    }
}

void Board::moveSelection(int key)
{
    if (m_cell_selected < 0)
        return;

    auto row = m_cell_selected / 9;
    auto col = m_cell_selected % 9;
    auto newRow = row;
    auto newCol = col;

    switch (key)
    {
    case Qt::Key_Up: case Qt::Key_K:
        newRow = (row > 0) ? row - 1 : row;
        break;
    case Qt::Key_Down: case Qt::Key_J:
        newRow = (row < 8) ? row + 1 : row;
        break;
    case Qt::Key_Left: case Qt::Key_H:
        newCol = (col > 0) ? col - 1 : col;
        break;
    case Qt::Key_Right: case Qt::Key_L:
        newCol = (col < 8) ? col + 1 : col;
        break;
    };

    if (newRow != row || newCol != col)
    {
        selectCell(newRow, newCol);
        repaint();
    }
}

void Board::setSelectedCellValue(int value)
{
    if (m_cell_selected >= 0 && !m_cells[m_cell_selected].isGiven())
        m_cells[m_cell_selected].setValue(value);
}

QRect Board::getCellRect(int row, int col) const
{
    return QRect(m_cell_offsets[col], m_cell_offsets[row], CellSize, CellSize);
}

int Board::getCellFromPos(int pos) const
{
    // check by thirds
    if (pos >= m_cell_offsets[0] && pos <= m_cell_offsets[2] + CellSize)
        return (pos - LineMajorWidth) / CellSize;
    else if (pos >= m_cell_offsets[3] && pos <= m_cell_offsets[5] + CellSize)
        return (pos - (2 * LineMajorWidth)) / CellSize;
    else if (pos >= m_cell_offsets[6] && pos <= m_cell_offsets[8] + CellSize)
        return (pos - (3 * LineMajorWidth)) / CellSize;

    return -1;
}

static bool isNavigationKey(int key)
{
    return (key == Qt::Key_Up ||
            key == Qt::Key_Down ||
            key == Qt::Key_Left ||
            key == Qt::Key_Right ||
            key == Qt::Key_H ||
            key == Qt::Key_J ||
            key == Qt::Key_K ||
            key == Qt::Key_L);
}

void Board::keyPressEvent(QKeyEvent* event)
{
    auto key = event->key();

    if (key >= Qt::Key_0 && key <= Qt::Key_9)
    {
        if (m_cell_selected >= 0)
        {
            auto num = key - Qt::Key_0;
            setSelectedCellValue(num);
        }
    }
    else if (isNavigationKey(key))
    {
        moveSelection(key);
    }
}

void Board::mousePressEvent(QMouseEvent* event)
{
    auto pos = event->localPos();

    int row = getCellFromPos(pos.y());
    int col = getCellFromPos(pos.x());
    if (row >= 0 && col >= 0)
    {
        selectCell(row, col);
        repaint();
    }
}

void Board::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    // blank the whole board
    painter.fillRect(0, 0, BoardSize, BoardSize, White);

    paintCells(painter);
    paintGridLines(painter);
}

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

void Board::paintCell(QPainter& painter, int row, int col, const Cell& cell)
{
    auto rect = getCellRect(row, col);

    // highlight cell
    if (cell.isSelected())
        painter.fillRect(rect, Yellow);
    else if (cell.isGiven())
        painter.fillRect(rect, LightGray);

    // draw cell number
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
