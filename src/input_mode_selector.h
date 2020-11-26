#ifndef INPUT_MODE_SELECTOR_H
#define INPUT_MODE_SELECTOR_H

#include "board/board_types.h"

#include <QFrame>

class InputModeSelector : public QFrame
{
    Q_OBJECT

public:
    InputModeSelector(QWidget* parent = nullptr);
    ~InputModeSelector();

signals:
    void inputModeChanged(InputMode);
};

#endif // INPUT_MODE_SELECTOR_H
