#ifndef BOARD_H
#define BOARD_H

#include "board_types.h"
#include "cell.h"

#include <array>

#include <QFont>
#include <QPen>
#include <QWidget>

class BoardGeometry;

class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget* parent = nullptr);
    ~Board();

    void setInputMode(InputMode);
    const Cell& cell(int, int) const;

protected:
    // override QWidget events here
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    void reset(bool withRepaint = true);
    void selectCell(int, int);
    void moveSelection(Direction);

private:
    std::shared_ptr<BoardGeometry> m_geo;
    InputMode m_mode;

    std::array<Cell, 81> m_cells;
    int8_t m_cell_selected;
};

#endif // BOARD_H
