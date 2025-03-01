#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    stackedWidget = new QStackedWidget(this);
    emptyWidget = new EmptyWidget(this);
    stackedWidget->addWidget(emptyWidget);
    stackedWidget->setCurrentWidget(emptyWidget);

    mainLayout->addWidget(stackedWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    connect(emptyWidget, &EmptyWidget::selectDirPressed, this, &MainWindow::onDirSelect);
}

void MainWindow::onDirSelect() {
}

MainWindow::~MainWindow() {}
