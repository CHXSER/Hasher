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
    loadingWidget = new LoadingWidget(this);
    stackedWidget->addWidget(emptyWidget);
    stackedWidget->addWidget(loadingWidget);
    stackedWidget->addWidget(comparisonWidget);
    stackedWidget->setCurrentWidget(emptyWidget);

    mainLayout->addWidget(stackedWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    connect(emptyWidget, &EmptyWidget::selectDirPressed, this, &MainWindow::onDirSelect);
}

void MainWindow::onDirSelect(const QString& dir) {
    if (dir.isEmpty()) {
        return;
    }
    stackedWidget->setCurrentWidget(loadingWidget);
    loadingWidget->setDirectory(dir);

    mediaProcessor = std::make_unique<MediaProcessor>(dir.toStdString());

    connect(mediaProcessor.get(), &MediaProcessor::progressUpdated,
        loadingWidget, &LoadingWidget::updateProgress);

    connect(mediaProcessor.get(), &MediaProcessor::processingFinished, this, [this]() {
        duplicates = mediaProcessor->getDuplicates();
        currentDupIndex = 0;
        if (duplicates.empty()) {
            stackedWidget->setCurrentWidget(emptyWidget);
            return;
        }
        comparisonWidget->setCurrentDuplicate(duplicates[currentDupIndex]);
        comparisonWidget->setDupLabel(currentDupIndex+1, duplicates.size());
        stackedWidget->setCurrentWidget(comparisonWidget);
    });

    mediaProcessor->startProcessing();

    connect(comparisonWidget, &ComparisonWidget::nextComparison, this, [this]() {
        if(currentDupIndex + 1 < duplicates.size()) {
            currentDupIndex++;
            comparisonWidget->setCurrentDuplicate(duplicates[currentDupIndex]);
            comparisonWidget->setDupLabel(currentDupIndex+1, duplicates.size());
        } else {
            // Create the widget for confirming the changes
        }
    });

    connect(comparisonWidget, &ComparisonWidget::previousComparison, this, [this]() {
        if(!currentDupIndex - 1 < 0) {
            currentDupIndex--;
            comparisonWidget->setCurrentDuplicate(duplicates[currentDupIndex]);
            comparisonWidget->setDupLabel(currentDupIndex+1, duplicates.size());
        }
    });
}

MainWindow::~MainWindow() {}
