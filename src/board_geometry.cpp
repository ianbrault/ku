/*
** src/board_geometry.cpp
*/

#include "board_geometry.h"

#include <QDebug>

static const auto board_geo = std::make_shared<BoardGeometry>();
std::shared_ptr<BoardGeometry> getBoardGeometry()
{
    return board_geo;
}

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

    // calculate cell inner offsets
    m_cell_inner_offsets[0] = 0;
    m_cell_inner_offsets[1] = CellSize / 3;
    m_cell_inner_offsets[2] = 2 * (CellSize / 3);
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

QRect BoardGeometry::cellInnerRect(uint8_t crow, uint8_t ccol, uint8_t irow, uint8_t icol) const
{
    // calculate outer offsets
    auto o_off_h = cellOffset(ccol);
    auto o_off_v = cellOffset(crow);

    // offset into the inner cell
    auto i_off_h = o_off_h + m_cell_inner_offsets[icol];
    auto i_off_v = o_off_v + m_cell_inner_offsets[irow];

    return QRect(i_off_h, i_off_v, CellSize / 3, CellSize / 3);
}

uint32_t BoardGeometry::cellOffset(uint8_t cn) const
{
    return m_cell_offsets[cn];
}

int8_t BoardGeometry::getCellFromPos(uint32_t pos) const
{
    int8_t rc = -1;

    // check by thirds
    if (pos >= m_cell_offsets[0] && pos <= m_cell_offsets[2] + CellSize)
    {
        rc = (pos - LineMajorWidth) / CellSize;
    }
    else if (pos >= m_cell_offsets[3] && pos <= m_cell_offsets[5] + CellSize)
    {
        rc = (pos - (2 * LineMajorWidth)) / CellSize;
    }
    else if (pos >= m_cell_offsets[6] && pos <= m_cell_offsets[8] + CellSize)
    {
        rc = (pos - (3 * LineMajorWidth)) / CellSize;
    }

    return rc;
}
