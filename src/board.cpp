/*
** src/board.cpp
*/

#include "board.h"
#include "board_painter.h"
#include "palette.h"

#include <cctype>

#include <QMessageBox>
#include <QMouseEvent>
#include <QTextStream>

Board::Board(QWidget *parent)
    : QWidget(parent), m_cell_selected(-1)
{
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

const Cell& Board::cell(int row, int col) const
{
    return m_cells[(row * 9) + col];
}

QRect Board::cellRect(int row, int col) const
{
    return QRect(m_cell_offsets[col], m_cell_offsets[row], CellSize, CellSize);
}

int Board::cellOffset(int cn) const
{
    return m_cell_offsets[cn];
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

void Board::puzzleLoadError(QString&& msg)
{
    // show a dialog box with the error message
    QMessageBox popup;

    popup.setText("Could not load the puzzle");
    popup.setInformativeText(
        QString("%1\n\nPuzzles should be specified in row-major order (with "
                "columns left-to-right, rows  top-to-bottom. All whitespace "
                "is ignored.\n")
                .arg(msg));

    popup.setStandardButtons(QMessageBox::Close);
    popup.setDefaultButton(QMessageBox::Close);
    popup.setStyleSheet("QLabel { min-width: 280px; }");
    popup.exec();

    reset();
}

void Board::loadPuzzleFromFile(QString&& filePath)
{
    // reset board before loading
    reset();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        puzzleLoadError("Could not open the puzzle file for reading");
        return;
    }

    QTextStream stream(&file);
    auto cell = 0;

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        for (const auto& c : line)
        {
            // check for an overspecified puzzle
            if (cell == 81)
            {
                puzzleLoadError("The puzzle file contains too many cells");
                return;
            }

            // ignore whitespace
            if (c.isSpace())
                continue;
            // "." indicates an empty cell
            else if (c == '.')
                cell++;
            else if (c.isDigit())
            {
                m_cells[cell].setValue(c.digitValue());
                m_cells[cell].setGiven(true);
                cell++;
            }
            else
            {
                // illegal character
                puzzleLoadError(QString("The puzzle file contains an invalid character: \"%1\"").arg(c));
                return;
            }
        }
    }

    // underspecified puzzles are okay, assume the remaining cells are empty
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
    {
        m_cells[m_cell_selected].setValue(value);
        repaint();
    }
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

void Board::paintEvent(QPaintEvent* event)
{
    BoardPainter painter(this);
    painter.paint(event);
}
