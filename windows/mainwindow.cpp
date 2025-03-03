#include "mainwindow.h"
#include "../models/mediaprocessor.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    stackedWidget = new QStackedWidget(this);
    emptyWidget = new EmptyWidget(this);
    comparisonWidget = new ComparisonWidget(this);
    stackedWidget->addWidget(emptyWidget);
    stackedWidget->addWidget(comparisonWidget);
    stackedWidget->setCurrentWidget(emptyWidget);

    mainLayout->addWidget(stackedWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    connect(emptyWidget, &EmptyWidget::selectDirPressed, this, &MainWindow::onDirSelect);
}

void MainWindow::onDirSelect(const QString& dir) {
    mediaProcessor = new MediaProcessor(dir.toStdString());
    for (auto& [file1, file2] : mediaProcessor->getDuplicates()) {
        qDebug() << "File1: " << file1;
        qDebug() << "File2: " << file2;
    }
    stackedWidget->setCurrentWidget(comparisonWidget);
}

MainWindow::~MainWindow() {
    if (mediaProcessor) delete mediaProcessor;
    if (duplicateManager) delete duplicateManager;
}
