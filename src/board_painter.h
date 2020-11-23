#ifndef BOARD_PAINTER_H
#define BOARD_PAINTER_H

#endif // BOARD_PAINTER_H

#include "cell.h"

#include <QPainter>

class Board;
class BoardGeometry;
class QPaintEvent;

class BoardPainter : public QPainter
{
public:
    BoardPainter(Board*);
    ~BoardPainter();

    void paint(QPaintEvent*);

private:
    void paintGridLines();
    void paintCells();
    void paintCell(int, int, const Cell&);
    void paintCellMarks(int row, int col, const Cell& cell);

private:
    BoardGeometry* m_geo;

    QPen m_pen_line_min;
    QPen m_pen_line_maj;

    QPen m_pen_text;
    QPen m_pen_text_given;

    QFont m_font_number;
    QFont m_font_mark;
};
