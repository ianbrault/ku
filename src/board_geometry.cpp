/*
** src/board_geometry.cpp
*/

#include "board_geometry.h"


BoardGeometry::BoardGeometry()
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
}

BoardGeometry::~BoardGeometry() {}

QSize BoardGeometry::boardSize() const
{
    return QSize(BoardSize, BoardSize);
}

uint32_t BoardGeometry::cellSize() const
{
    return CellSize;
}


QRect BoardGeometry::cellRect(uint8_t row, uint8_t col) const
{
    return QRect(m_cell_offsets[col], m_cell_offsets[row], CellSize, CellSize);
}

uint32_t BoardGeometry::cellOffset(uint8_t cn) const
{
    return m_cell_offsets[cn];
}

int8_t BoardGeometry::getCellFromPos(uint32_t pos) const
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
