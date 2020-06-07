#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class MainView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setupMenuBar();
    void openPuzzleFileDialog();

private:
    MainView* m_view;
};

#endif // MAIN_WINDOW_H
