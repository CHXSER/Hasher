#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget(this);
    emptyWidget = new EmptyWidget(this);

    layout->addWidget(stackedWidget);
    stackedWidget->addWidget(emptyWidget);
    stackedWidget->setCurrentWidget(emptyWidget);

    setCentralWidget(stackedWidget);
}

void MainWindow::onDirSelect() {}

MainWindow::~MainWindow() {}
