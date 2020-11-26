#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QWidget>

class Board;
class InputModeSelector;

class MainView : public QWidget
{
    Q_OBJECT

public:
    MainView(QWidget* parent = nullptr);
    ~MainView();

private:
    void setupLayout();

private:
    Board* m_board;
    InputModeSelector* m_mode_selector;
};

#endif // MAIN_VIEW_H
