/*
** src/cell.cpp
*/

#include "cell.h"

#include <algorithm>

#include <QDebug>

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

void Cell::cornerMarks(Cell::CellBufData& buf) const
{
    m_cnr_marks.sorted(buf);
}

void Cell::centerMarks(Cell::CellBufData& buf) const
{
    m_ctr_marks.sorted(buf);
}

void Cell::clear()
{
    m_value = -1;
    m_cnr_marks.clear();
    m_ctr_marks.clear();

    m_selected = false;
    m_given = false;
}

void Cell::toggleSelect()
{
    m_selected = !m_selected;
}

void Cell::setGiven(bool given)
{
    m_given = given;
}

void Cell::onKeyPress(InputMode mode, int key)
{
    int8_t value = key - Qt::Key_0;

    if (m_given)
    {
        // no key events are accepted on givens
    }
    // backspace actions are independent of the input mode
    else if (key == Qt::Key_Backspace)
    {
        // if a value is set, delete and fall back to corner/center marks
        if (m_value >= 0)
        {
            m_value = -1;
        }
        // otherwise, all marks are cleared
        else
        {
            m_cnr_marks.clear();
            m_ctr_marks.clear();
        }
    }
    else if (mode == InputMode::Normal)
    {
        // in normal mode, just set the value
        qDebug() << "Cell::onKeyPress: set cell value" << value;
        m_value = value;
    }
    else
    {
        CellBuf* marks;
        switch (mode)
        {
        case InputMode::Corner:
            marks = &m_cnr_marks;
            break;
        case InputMode::Center:
            marks = &m_ctr_marks;
            break;
        default:
            // this should be unreachable
            assert(0);
        };

        auto it = marks->find(value);
        if (it != marks->data.end())
        {
            // if the value is currently in the marks, it should be removed
            qDebug().nospace() << "Cell::onKeyPress: remove cell mark " << value << " (mode=" << mode << ")";
            marks->remove(it);
        }
        else
        {
            // otherwise, add it
            qDebug().nospace() << "Cell::onKeyPress: add cell mark " << value << " (mode=" << mode << ")";
            marks->insert(value);
            // value should be cleared whenever a mark is set
            m_value = -1;
        }
    }
}

/*
** Cell::RingBuf
*/

bool Cell::CellBuf::isEmpty() const
{
    return data[0] < 0 && data[1] < 0 && data[2] < 0 && data[3] < 0;
}

void Cell::CellBuf::insert(int8_t value)
{
    if (m_cursor < 4)
    {
        data[m_cursor++] = value;
    }
}

Cell::CellBufData::const_iterator Cell::CellBuf::find(int8_t value) const
{
    return std::find(data.begin(), data.end(), value);
}

void Cell::CellBuf::remove(Cell::CellBufData::const_iterator it)
{
    auto i = std::distance(data.cbegin(), it);

    // remove the value
    data[i] = -1;

    // shift all items to the right of the removed value so that data in the
    // buffer remains contiguous
    for (; i < 3 && data[i + 1] >= 0; i++)
    {
        std::swap(data[i], data[i + 1]);
    }

    // rewind the cursor by 1
    m_cursor--;
}

void Cell::CellBuf::clear()
{
    data.fill(-1);
    m_cursor = 0;
}

void Cell::CellBuf::sorted(Cell::CellBufData& buf) const
{
    // clear the provided buffer
    buf.fill(-1);

    // use the lower 9 bits to track which numbers are present
    uint16_t bitfield = 0;
    for (const auto& n : data)
    {
        bitfield |= (n >= 0) ? (1 << n) : 0;
    }

    // fill the buffer with the numbers that are present
    uint8_t n_nums = 0;
    for (auto i = 1; i <= 9; i++)
    {
        if (bitfield & (1 << i))
        {
            buf[n_nums++] = i;
        }
    }
}

QString Cell::CellBuf::dataToString() const
{
    return QString("data=[%1,%2,%3,%4]")
        .arg(QString::number(data[0]))
        .arg(QString::number(data[1]))
        .arg(QString::number(data[2]))
        .arg(QString::number(data[3]));
}
