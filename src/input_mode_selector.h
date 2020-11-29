#ifndef INPUT_MODE_SELECTOR_H
#define INPUT_MODE_SELECTOR_H

#include "types.h"
#include "widget.h"

class MainView;
class QRadioButton;

class InputModeSelector : public Widget
{
    Q_OBJECT

public:
    InputModeSelector(MainView*);
    ~InputModeSelector();

protected:
    // override QWidget events here
    void onKeyEvent(QKeyEvent*) override;

private:
    void setupLayout();
    void cycleInputMode();

signals:
    void inputModeChanged(InputMode);

private:
    QRadioButton* m_radio_input_mode_normal;
    QRadioButton* m_radio_input_mode_corner;
    QRadioButton* m_radio_input_mode_center;
    QRadioButton* m_selected;

    std::map<InputMode, QRadioButton*> m_type_to_button;
    std::map<QRadioButton*, InputMode> m_button_to_type;
};

#endif // INPUT_MODE_SELECTOR_H
