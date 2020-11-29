/*
** src/main_view.cpp
*/

#include "board/board.h"
#include "divider.h"
#include "input_mode_selector.h"
#include "main_view.h"

#include <QLabel>
#include <QVBoxLayout>

MainView::MainView(QWidget *parent)
    : QWidget(parent)
{
    m_board = new Board();
    m_mode_selector = new InputModeSelector();

    connect(m_mode_selector, &InputModeSelector::inputModeChanged,
            m_board, &Board::setInputMode);

    setupLayout();
}

MainView::~MainView() {}

void MainView::setupLayout()
{
    auto layout = new QHBoxLayout();
    layout->addWidget(m_board);

    // the gutter contains the control panels to the right of the board
    auto gutter = new QVBoxLayout();
    gutter->addWidget(m_mode_selector);
    gutter->addWidget(new Divider());
    gutter->addStretch();

    layout->addSpacing(16);
    layout->addLayout(gutter);

    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(50, 50, 32, 50);
    setLayout(layout);
}
