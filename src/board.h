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

public:
    // board dimension definitions
    enum Size {
        LineMinorWidth  = 1,
        LineMajorWidth  = 4,
        LineMajorOffset = LineMajorWidth / 2,
        CellSize        = 72,
        BoardSize       = (LineMajorWidth * 4) + (CellSize * 9),
        NumberSize      = 40,
    };
    Q_ENUM(Size);

public:
    Board(QWidget* parent = nullptr);
    ~Board();

    const Cell& cell(int, int) const;
    QRect cellRect(int, int) const;
    int   cellOffset(int) const;
    void  loadPuzzleFromFile(QString&& filePath);

protected:
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    void reset(bool withRepaint = true);
    void selectCell(int, int);
    void moveSelection(int);
    void setSelectedCellValue(int);
    int  getCellFromPos(int) const;
    void puzzleLoadError(QString&&);

private:
    std::array<int,  9>  m_cell_offsets;
    std::array<Cell, 81> m_cells;
    int m_cell_selected;
};

#endif // BOARD_H
