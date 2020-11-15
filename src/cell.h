#ifndef CELL_H
#define CELL_H

#include <array>
#include <cstdint>

class Cell
{
public:
    Cell();
    ~Cell();

    int8_t value() const;
    bool isSelected() const;
    bool isGiven() const;

    void clear();
    void setValue(int8_t);
    void toggleSelect();
    void setGiven(bool);

private:
    int8_t m_value;
    std::array<int8_t, 4> m_cnr_marks{-1};  // corner marks
    std::array<int8_t, 4> m_ctr_marks{-1};  // center marks

    bool m_selected;
    bool m_given;
};

#endif // CELL_H
