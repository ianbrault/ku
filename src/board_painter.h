#ifndef BOARD_PAINTER_H
#define BOARD_PAINTER_H

#endif // BOARD_PAINTER_H

#include "cell.h"

#include <QPainter>

class Board;
class QPaintEvent;

class BoardPainter : public QPainter
{
public:
    BoardPainter(Board*);
    ~BoardPainter();

    void paint(QPaintEvent*);

private:
    void paintGridLines();
    void paintCell(int, int, const Cell&);
    void paintCells();

private:
    QPen m_pen_line_min;
    QPen m_pen_line_maj;

    QPen m_pen_text;
    QPen m_pen_text_given;

    QFont m_font_number;
};
