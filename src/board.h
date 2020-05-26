#ifndef BOARD_H
#define BOARD_H

#include <array>

#include <QPen>
#include <QWidget>

class Cell;

class Board : public QWidget
{
    Q_OBJECT

    // board dimension definitions
    static const auto LineMinorWidth = 1;
    static const auto LineMajorWidth = 4;
    static const auto LineMajorOffset = LineMajorWidth / 2;
    static const auto CellSize = 72;
    static const auto BoardSize = (LineMajorWidth * 4) + (LineMinorWidth * 6) + (CellSize * 9);

public:
    Board(QWidget* parent = nullptr);
    ~Board();

protected:
    void paintEvent(QPaintEvent*) override;

private:
    void paintGridLines(QPainter&);

private:
    std::array<Cell*, 81> m_cells;

    QPen m_pen_min;
    QPen m_pen_maj_outer;
    QPen m_pen_maj_inner;
};

#endif // BOARD_H
