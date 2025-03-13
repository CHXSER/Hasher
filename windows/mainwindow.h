#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QString>
#include <memory>

#include "../models/duplicatemanager.h"
#include "../models/mediaprocessor.h"

#include "../widgets/emptywidget.h"
#include "../widgets/comparisonwidget.h"
#include "../widgets/loadingwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDirSelect(const QString& dir);

private:
    QStackedWidget* stackedWidget;
    EmptyWidget* emptyWidget;
    ComparisonWidget* comparisonWidget;
    LoadingWidget* loadingWidget;
    DuplicateManager* duplicateManager;
    std::unique_ptr<MediaProcessor> mediaProcessor;
    void updateUI();
};
#endif // MAINWINDOW_H
