#ifndef INPUT_MODE_SELECTOR_H
#define INPUT_MODE_SELECTOR_H

#include "board/board_types.h"

#include <QWidget>

class QRadioButton;

class InputModeSelector : public QWidget
{
    Q_OBJECT

public:
    InputModeSelector(QWidget* parent = nullptr);
    ~InputModeSelector();

private:
    void setupLayout();

signals:
    void inputModeChanged(InputMode);

private:
    QRadioButton* m_radio_input_mode_normal;
    QRadioButton* m_radio_input_mode_corner;
    QRadioButton* m_radio_input_mode_center;
};

#endif // INPUT_MODE_SELECTOR_H
