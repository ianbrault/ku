/*
** src/cell.cpp
*/

#include "cell.h"

#include <QLabel>
#include <QVBoxLayout>

Cell::Cell(int row, int col, QWidget *parent)
    : QWidget(parent), m_row(row), m_col(col)
{
    auto layout = new QVBoxLayout();
    layout->addWidget(new QLabel("0"));
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);

    setStyleSheet("font-size: 24px");
}

Cell::~Cell() {}
