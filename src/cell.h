#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Cell();
    ~Cell();

    char value() const;
    bool isSelected() const;

private:
    char m_value;
    bool m_selected;
};

#endif // CELL_H
