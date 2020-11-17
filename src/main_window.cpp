/*
** src/main_window.cpp
*/

#include "main_view.h"
#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_view = new MainView();
    setCentralWidget(m_view);

    setStyleSheet("background-color: #fff");
    setupMenuBar();
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenuBar()
{
    // FIXME: implement for a menu bar
}
