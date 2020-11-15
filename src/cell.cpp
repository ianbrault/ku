/*
** src/cell.cpp
*/

#include "cell.h"

Cell::Cell()
    : m_value(-1), m_selected(false), m_given(false)
{

}

Cell::~Cell() {}

int8_t Cell::value() const
{
    return m_value;
}

bool Cell::isSelected() const
{
    return m_selected;
}

bool Cell::isGiven() const
{
    return m_given;
}

void Cell::clear()
{
    m_value = -1;
    m_cnr_marks.fill(-1);
    m_ctr_marks.fill(-1);

    m_selected = false;
    m_given = false;
}

void Cell::setValue(int8_t value)
{
    m_value = value;
}

void Cell::toggleSelect()
{
    m_selected = !m_selected;
}

void Cell::setGiven(bool given)
{
    m_given = given;
}
