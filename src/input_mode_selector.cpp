/*
** src/input_mode_selector.cpp
*/

#include "input_mode_selector.h"
#include "palette.h"

#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

InputModeSelector::InputModeSelector(QWidget* parent)
    : QFrame(parent)
{
    setStyleSheet(
        QString("QFrame{border:1px solid %1} QFrame>*{border:none;color:%1}")
            .arg(BlackStr));

    auto layout = new QVBoxLayout();

    auto title = new QLabel("Input Mode");
    // TODO: style the title

    auto radio_normal = new QRadioButton("Normal");
    auto radio_corner = new QRadioButton("Corner");
    auto radio_center = new QRadioButton("Center");

    // InputMode::Normal by default
    radio_normal->setChecked(true);

    // set up signals
    connect(radio_normal, &QRadioButton::pressed, this, [&](){
        emit inputModeChanged(InputMode::Normal);
    });
    connect(radio_corner, &QRadioButton::pressed, this, [&](){
        emit inputModeChanged(InputMode::Corner);
    });
    connect(radio_center, &QRadioButton::pressed, this, [&](){
        emit inputModeChanged(InputMode::Center);
    });

    layout->addWidget(title);
    layout->addWidget(radio_normal);
    layout->addWidget(radio_corner);
    layout->addWidget(radio_center);
    setLayout(layout);
}

InputModeSelector::~InputModeSelector() {}
