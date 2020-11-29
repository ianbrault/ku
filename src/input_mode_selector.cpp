/*
** src/input_mode_selector.cpp
*/

#include "icon.h"
#include "input_mode_selector.h"
#include "styles.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

InputModeSelector::InputModeSelector(QWidget* parent)
    : QWidget(parent)
{
    // add spacing to the left of the text
    m_radio_input_mode_normal = new QRadioButton(" Normal");
    m_radio_input_mode_corner = new QRadioButton(" Corner");
    m_radio_input_mode_center = new QRadioButton(" Center");

    // InputMode::Normal by default
    m_radio_input_mode_normal->setChecked(true);

    // set up signals
    connect(m_radio_input_mode_normal, &QRadioButton::pressed, this, [&](){
        emit inputModeChanged(InputMode::Normal);
    });
    connect(m_radio_input_mode_corner, &QRadioButton::pressed, this, [&](){
        emit inputModeChanged(InputMode::Corner);
    });
    connect(m_radio_input_mode_center, &QRadioButton::pressed, this, [&](){
        emit inputModeChanged(InputMode::Center);
    });

    setupLayout();
}

InputModeSelector::~InputModeSelector() {}

void InputModeSelector::setupLayout()
{
    auto layout = new QVBoxLayout();
    layout->setSpacing(8);

    QFont sidebarTitleFont;
    sidebarTitleFont.setPointSize(16);
    sidebarTitleFont.setWeight(QFont::Medium);

    auto titleText = new QLabel("Input Mode");
    titleText->setFont(sidebarTitleFont);

    auto titleIcon = new Icon(":/pencil.svg", 18);

    auto titleRow = new QHBoxLayout();
    titleRow->addWidget(titleText);
    titleRow->addStretch();
    titleRow->addWidget(titleIcon);
    titleRow->setAlignment(Qt::AlignCenter);
    titleRow->setMargin(0);

    layout->addLayout(titleRow);
    layout->addWidget(m_radio_input_mode_normal);
    layout->addWidget(m_radio_input_mode_corner);
    layout->addWidget(m_radio_input_mode_center);

    setLayout(layout);
    setFixedWidth(150);
}
