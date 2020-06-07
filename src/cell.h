#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Cell();
    ~Cell();

    char value() const;
    bool isSelected() const;
    bool isGiven() const;

    void clear();
    void setValue(char);
    void toggleSelect();
    void setGiven(bool);

private:
    char m_value;
    bool m_selected;
    bool m_given;
};

#endif // CELL_H
