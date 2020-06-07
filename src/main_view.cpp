/*
** src/main_view.cpp
*/

#include "board.h"
#include "main_view.h"

#include <QLabel>
#include <QVBoxLayout>

MainView::MainView(QWidget *parent)
    : QWidget(parent)
{
    m_board = new Board();

    auto layout = new QVBoxLayout();
    layout->addWidget(m_board);

    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(40, 16, 40, 40);
    setLayout(layout);
}

MainView::~MainView() {}

void MainView::loadPuzzleFromFile(QString&& filePath)
{
    m_board->loadPuzzleFromFile(std::move(filePath));
}
