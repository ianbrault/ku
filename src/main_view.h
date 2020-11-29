#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "widget.h"

#include <QWidget>

class Board;
class InputModeSelector;

class MainView : public QWidget
{
    Q_OBJECT

public:
    MainView(QWidget* parent = nullptr);
    ~MainView();

    /*
    ** MainView grabs the keyboard and is responsible for dispatching key press
    ** events to child widgets; widgets should register which keys they wish to
    ** receive events for using this function through the `parent` parameter
    */
    void registerKeys(Widget*, std::vector<int>);

protected:
    // override QWidget events here
    void keyPressEvent(QKeyEvent*) override;

private:
    void setupLayout();

private:
    Board* m_board;
    InputModeSelector* m_mode_selector;

    std::map<int, Widget*> m_registered_keys;
};

#endif // MAIN_VIEW_H
