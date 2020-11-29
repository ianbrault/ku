#ifndef CELL_H
#define CELL_H

#include "../types.h"

#include <array>
#include <cstdint>

class Cell
{
    typedef std::array<int8_t, 4> CellBufData;

public:
    Cell();
    ~Cell();

    int8_t value() const;
    bool isSelected() const;
    bool isGiven() const;
    void cornerMarks(CellBufData&) const;
    void centerMarks(CellBufData&) const;

    void clear();
    void toggleSelect();
    void setGiven(bool);

    void onKeyPress(InputMode, int);

private:
    /*
    ** buffer structure used for corner/center marks
    */
    struct CellBuf
    {
        CellBufData data{-1,-1,-1,-1};
        uint8_t m_cursor = 0;

        bool isEmpty() const;
        void insert(int8_t value);
        CellBufData::const_iterator find(int8_t) const;
        void remove(CellBufData::const_iterator);
        void clear();
        void sorted(CellBufData&) const;
        // for debug use only!
        QString dataToString() const;
    };

private:
    int8_t m_value;
    CellBuf m_cnr_marks;  // corner marks
    CellBuf m_ctr_marks;  // center marks

    bool m_selected;
    bool m_given;
};

#endif // CELL_H
