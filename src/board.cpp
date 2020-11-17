/*
** src/board.cpp
*/

#include "board.h"
#include "board_geometry.h"
#include "board_painter.h"
#include "palette.h"

#include <cctype>

#include <QMessageBox>
#include <QMouseEvent>
#include <QTextStream>

Board::Board(QWidget *parent)
    : QWidget(parent), m_mode(Normal), m_cell_selected(-1)
{
    // FIXME: this should share the same instance with the BoardPainter
    m_geo = new BoardGeometry();

    setFixedSize(m_geo->boardSize());
    grabKeyboard();
}

Board::~Board()
{
    delete m_geo;
}

void Board::setInputMode(InputMode mode)
{
    m_mode = mode;
}

const Cell& Board::cell(int row, int col) const
{
    return m_cells[(row * 9) + col];
}

void Board::reset(bool withRepaint)
{
    // clear all cells and selection
    for (auto& cell : m_cells)
        cell.clear();
    m_cell_selected = -1;

    if (withRepaint)
        repaint();
}

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

void Board::moveSelection(Direction dir)
{
    if (m_cell_selected < 0)
        return;

    auto row = m_cell_selected / 9;
    auto col = m_cell_selected % 9;
    auto newRow = row;
    auto newCol = col;

    switch (dir)
    {
    case None:
        break;
    case Up:
        newRow = (row > 0) ? row - 1 : row;
        break;
    case Down:
        newRow = (row < 8) ? row + 1 : row;
        break;
    case Left:
        newCol = (col > 0) ? col - 1 : col;
        break;
    case Right:
        newCol = (col < 8) ? col + 1 : col;
        break;
    };

    if (newRow != row || newCol != col)
    {
        selectCell(newRow, newCol);
        repaint();
    }
}

void Board::setSelectedCellValue(int8_t value)
{
    if (m_cell_selected >= 0 && !m_cells[m_cell_selected].isGiven())
    {
        m_cells[m_cell_selected].setValue(value);
        repaint();
    }
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

Board::Direction Board::keyToDirection(int key)
{
    auto dir = None;

    if (key == Qt::Key_Up || key == Qt::Key_K)
        dir = Up;
    else if (key == Qt::Key_Down || key == Qt::Key_J)
        dir = Down;
    else if (key == Qt::Key_Left || key == Qt::Key_H)
        dir = Left;
    else if (key == Qt::Key_Right || key == Qt::Key_L)
        dir = Right;

    return dir;
}

void Board::keyPressEvent(QKeyEvent* event)
{
    auto key = event->key();

    if (key >= Qt::Key_0 && key <= Qt::Key_9)
        setSelectedCellValue(key - Qt::Key_0);
    else if (key == Qt::Key_Backspace)
        setSelectedCellValue(-1);
    else if (isNavigationKey(key))
        moveSelection(keyToDirection(key));
}

void Board::mousePressEvent(QMouseEvent* event)
{
    auto pos = event->localPos();

    int row = m_geo->getCellFromPos(pos.y());
    int col = m_geo->getCellFromPos(pos.x());
    if (row >= 0 && col >= 0)
    {
        selectCell(row, col);
        repaint();
    }
}

void Board::paintEvent(QPaintEvent* event)
{
    BoardPainter painter(this);
    painter.paint(event);
}
