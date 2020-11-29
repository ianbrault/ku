/*
** src/input_mode_selector.cpp
*/

#include "icon.h"
#include "input_mode_selector.h"
#include "main_view.h"
#include "styles.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

InputModeSelector::InputModeSelector(MainView* parent)
    : Widget()
{            
    // add spacing to the left of the text
    m_radio_input_mode_normal = new QRadioButton(" Normal");
    m_radio_input_mode_corner = new QRadioButton(" Corner");
    m_radio_input_mode_center = new QRadioButton(" Center");

    m_type_to_button = {
        {InputMode::Normal, m_radio_input_mode_normal},
        {InputMode::Corner, m_radio_input_mode_corner},
        {InputMode::Center, m_radio_input_mode_center},
    };
    m_button_to_type = {
        {m_radio_input_mode_normal, InputMode::Normal},
        {m_radio_input_mode_corner, InputMode::Corner},
        {m_radio_input_mode_center, InputMode::Center},
    };

    // InputMode::Normal by default
    m_radio_input_mode_normal->setChecked(true);
    m_selected = m_radio_input_mode_normal;

    // set up signals
    connect(m_radio_input_mode_normal, &QRadioButton::pressed, this, [&](){
        m_selected = m_radio_input_mode_normal;
        emit inputModeChanged(InputMode::Normal);
    });
    connect(m_radio_input_mode_corner, &QRadioButton::pressed, this, [&](){
        m_selected = m_radio_input_mode_corner;
        emit inputModeChanged(InputMode::Corner);
    });
    connect(m_radio_input_mode_center, &QRadioButton::pressed, this, [&](){
        m_selected = m_radio_input_mode_center;
        emit inputModeChanged(InputMode::Center);
    });

    // register keys
    parent->registerKeys(this, {Qt::Key_Space});

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

    QFont helpTextFont;
    helpTextFont.setPointSize(11);

    auto titleText = new QLabel("Input Mode");
    titleText->setFont(sidebarTitleFont);

    auto titleIcon = new Icon(":/pencil.svg", 18);

    auto titleRow = new QHBoxLayout();
    titleRow->addWidget(titleText);
    titleRow->addStretch();
    titleRow->addWidget(titleIcon);
    titleRow->setAlignment(Qt::AlignCenter);
    titleRow->setMargin(0);

    auto helpText = new QLabel("[Space] to cycle mode");
    helpText->setFont(helpTextFont);
    helpText->setStyleSheet(
        QString("color:rgb(%1,%2,%3)")
            .arg(Gray.red()).arg(Gray.green()).arg(Gray.blue()));

    layout->addLayout(titleRow);
    layout->addSpacing(4);
    layout->addWidget(m_radio_input_mode_normal);
    layout->addWidget(m_radio_input_mode_corner);
    layout->addWidget(m_radio_input_mode_center);
    layout->addSpacing(6);
    layout->addWidget(helpText);

    setLayout(layout);
    setFixedWidth(150);
}

void InputModeSelector::cycleInputMode()
{
    auto new_mode = (InputMode) ((m_button_to_type[m_selected] + 1) % InputMode::InputModeMax);

    // deselect previously-selected radio button
    m_selected->setChecked(false);
    m_selected = m_type_to_button[new_mode];

    // select new radio button and emit mode changed
    m_selected->setChecked(true);
    emit inputModeChanged(new_mode);
}

void InputModeSelector::onKeyEvent(QKeyEvent* event)
{
    auto key = event->key();

    if (key == Qt::Key_Space)
    {
        cycleInputMode();
    }
}
