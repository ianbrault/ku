#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "../types.h"
#include "../widget.h"

#include <array>

#include <QFont>
#include <QPen>

class BoardGeometry;
class MainView;

class Board : public Widget
{
    Q_OBJECT

public:
    Board(MainView*);
    ~Board();

    const Cell& cell(int, int) const;

protected:
    // override QWidget events here
    void onKeyEvent(QKeyEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    void reset(bool withRepaint = true);
    void selectCell(int, int);
    void moveSelection(Direction);

public slots:
    void setInputMode(InputMode);

private:
    std::shared_ptr<BoardGeometry> m_geo;
    InputMode m_mode;

    std::array<Cell, 81> m_cells;
    int8_t m_cell_selected;
};

#endif // BOARD_H
