/*
** src/main_window.cpp
*/

#include "main_view.h"
#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new MainView());
    setStyleSheet("background-color: #fff");
}

MainWindow::~MainWindow() {}
