#ifndef CELL_H
#define CELL_H

#include <QWidget>

class Cell : public QWidget
{
    Q_OBJECT

public:
    Cell(int row, int col, QWidget* parent = nullptr);
    ~Cell();

private:
    void setBorders();

private:
    int m_row;
    int m_col;
};

#endif // CELL_H
