/*
** src/main_view.cpp
*/

#include "board/board.h"
#include "divider.h"
#include "input_mode_selector.h"
#include "main_view.h"

#include <QDebug>
#include <QKeyEvent>
#include <QLabel>
#include <QVBoxLayout>

MainView::MainView(QWidget *parent)
    : QWidget(parent)
{
    m_board = new Board(this);
    m_mode_selector = new InputModeSelector(this);

    connect(m_mode_selector, &InputModeSelector::inputModeChanged,
            m_board, &Board::setInputMode);

    setupLayout();
    grabKeyboard();
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

void MainView::registerKeys(Widget* widget, std::vector<int> keys)
{
    for (const auto& key : keys)
    {
        // first-come, first-serve (should be no overlap anyways)
        auto it = m_registered_keys.find(key);
        if (it != m_registered_keys.end())
        {
            qDebug().nospace()
               << "MainView::reigsterKeys: key " << key << " is already registered for "
               << Qt::hex << *it << ", cannot register for " << Qt::hex << widget;
        }

        m_registered_keys.insert({key, widget});
    }
}

void MainView::keyPressEvent(QKeyEvent* event)
{
    auto it = m_registered_keys.find(event->key());
    if (it != m_registered_keys.end())
    {
        it->second->onKeyEvent(event);
    }
}
