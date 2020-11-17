#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QWidget>

class Board;

class MainView : public QWidget
{
    Q_OBJECT

public:
    MainView(QWidget* parent = nullptr);
    ~MainView();

private:
    Board* m_board;
};

#endif // MAIN_VIEW_H
