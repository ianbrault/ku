/*
** src/board.cpp
*/

#include "board.h"
#include "board_geometry.h"
#include "board_painter.h"
#include "../main_view.h"
#include "../styles.h"

#include <cctype>

#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTextStream>

Board::Board(MainView* parent)
    : Widget(), m_mode(InputMode::Normal), m_cell_selected(-1)
{
    m_geo = getBoardGeometry();

    // register keys
    parent->registerKeys(this, {
        Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4, Qt::Key_5, Qt::Key_6, Qt::Key_7, Qt::Key_8, Qt::Key_9,
        Qt::Key_Backspace, Qt::Key_Up, Qt::Key_Down, Qt::Key_Left, Qt::Key_Right,
        // Vim-style keybindings, might want to hide these behind a flag
        Qt::Key_H, Qt::Key_J, Qt::Key_K, Qt::Key_L,
    });

    setFixedSize(m_geo->boardSize());
}

Board::~Board() {}

void Board::setInputMode(InputMode mode)
{
    m_mode = mode;
    qDebug().noquote() << "Board::setInputMode: set input mode" << inputModeToString(mode);
}

const Cell& Board::cell(int row, int col) const
{
    return m_cells[(row * 9) + col];
}

void Board::reset(bool withRepaint)
{
    // clear all cells and selection
    for (auto& cell : m_cells)
    {
        cell.clear();
    }
    m_cell_selected = -1;

    if (withRepaint)
    {
        repaint();
    }
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
        {
            m_cells[m_cell_selected].toggleSelect();
        }
        m_cell_selected = target;
    }
}

void Board::moveSelection(Direction dir)
{
    if (m_cell_selected < 0)
    {
        return;
    }

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
    }
}

static bool isCellKey(int key)
{
    return (key > Qt::Key_0 && key <= Qt::Key_9) || key == Qt::Key_Backspace;
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

void Board::onKeyEvent(QKeyEvent* event)
{
    auto key = event->key();
    bool paint = false;

    if (isCellKey(key))
    {
        // send key event to selected cell(s)
        if (m_cell_selected >= 0)
        {
            // FIXME: should Cell::onKeyPress return whether to repaint?
            m_cells[m_cell_selected].onKeyPress(m_mode, key);
            paint = true;
        }
    }
    else if (isNavigationKey(key))
    {
        moveSelection(keyToDirection(key));
        paint = true;
    }

    if (paint)
    {
        repaint();
    }
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
