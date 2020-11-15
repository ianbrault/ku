#ifndef BOARD_H
#define BOARD_H

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
    enum InputMode {
        Normal,
        Corner,
        Center,
    };
    Q_ENUM(InputMode);

    enum Direction {
        None,
        Up,
        Down,
        Left,
        Right,
    };
    Q_ENUM(Direction);
    Direction keyToDirection(int);

public:
    Board(QWidget* parent = nullptr);
    ~Board();

    void setInputMode(InputMode);
    const Cell& cell(int, int) const;
    void loadPuzzleFromFile(QString&& filePath);

protected:
    // override QWidget events here
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    void reset(bool withRepaint = true);
    void selectCell(int, int);
    void moveSelection(Direction);
    void setSelectedCellValue(int8_t);
    int  getCellFromPos(int) const;
    void puzzleLoadError(QString&&);

private:
    BoardGeometry* m_geo;
    InputMode m_mode;

    std::array<Cell, 81> m_cells;
    int8_t m_cell_selected;
};

#endif // BOARD_H
