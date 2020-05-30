#ifndef BOARD_H
#define BOARD_H

#include "cell.h"

#include <array>

#include <QFont>
#include <QPen>
#include <QWidget>

class Board : public QWidget
{
    Q_OBJECT

    // board dimension definitions
    static const auto LineMinorWidth = 1;
    static const auto LineMajorWidth = 4;
    static const auto LineMajorOffset = LineMajorWidth / 2;
    static const auto CellSize = 72;
    static const auto BoardSize = (LineMajorWidth * 4) + (CellSize * 9);

    static const auto NumberSize = 40;

public:
    Board(QWidget* parent = nullptr);
    ~Board();

protected:
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    void  selectCell(int, int);
    void  moveSelection(int);

    QRect getCellRect(int, int) const;
    int   getCellFromPos(int) const;

    void  paintGridLines(QPainter&);
    void  paintCell(QPainter&, int, int, const Cell&);
    void  paintCells(QPainter&);

private:
    std::array<int,  9>  m_cell_offsets;
    std::array<Cell, 81> m_cells;
    int m_cell_selected;

    QPen m_pen_min;
    QPen m_pen_maj;

    QFont m_font_number;
};

#endif // BOARD_H
