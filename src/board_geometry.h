#ifndef BOARD_GEOMETRY_H
#define BOARD_GEOMETRY_H

#include <array>

#include <QRect>
#include <QSize>

class BoardGeometry
{
public:
    // board dimension definitions
    enum Size: uint32_t
    {
        LineMinorWidth  = 1,
        LineMajorWidth  = 4,
        LineMajorOffset = LineMajorWidth / 2,
        CellSize        = 72,
        BoardSize       = (LineMajorWidth * 4) + (CellSize * 9),
        NumberSize      = 40,
        MarkSize        = 16,
    };

public:
    BoardGeometry();
    ~BoardGeometry();

    QSize    boardSize() const;
    uint32_t cellSize() const;
    QRect    cellRect(uint8_t, uint8_t) const;
    QRect    cellInnerRect(uint8_t, uint8_t, uint8_t, uint8_t) const;
    uint32_t cellOffset(uint8_t) const;
    int8_t   getCellFromPos(uint32_t pos) const;

private:
    std::array<uint32_t, 9> m_cell_offsets;
    std::array<uint32_t, 3> m_cell_inner_offsets;
};

#endif
