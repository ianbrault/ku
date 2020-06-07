/*
** src/main_window.cpp
*/

#include "main_view.h"
#include "main_window.h"

#include <QDir>
#include <QFileDialog>
#include <QMenuBar>

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
    auto fileMenu = menuBar()->addMenu("&File");

    auto openPuzzle = fileMenu->addAction("&Open Puzzle");
    openPuzzle->setShortcuts(QKeySequence::Open);
    connect(openPuzzle, &QAction::triggered, this, &MainWindow::openPuzzleFileDialog);
}

void MainWindow::openPuzzleFileDialog()
{
    // open a file dialog window
    auto fileName = QFileDialog::getOpenFileName(
        this, "Open puzzle file", QDir::homePath(), "Text files (*.txt)");

    if (!fileName.isEmpty())
        m_view->loadPuzzleFromFile(std::move(fileName));
}
