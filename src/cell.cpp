/*
** src/cell.cpp
*/

#include "cell.h"

Cell::Cell()
    : m_value(-1), m_selected(false)
{

}

Cell::~Cell() {}

char Cell::value() const
{
    return m_value;
}

bool Cell::isSelected() const
{
    return m_selected;
}

void Cell::toggleSelect()
{
    m_selected = !m_selected;
}
