#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QString>

#include "../models/mediaprocessor.h"
#include "../models/duplicatemanager.h"

#include "../widgets/emptywidget.h"
#include "../widgets/comparisonwidget.h"

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
    MediaProcessor* mediaProcessor;
    DuplicateManager* duplicateManager;
    void updateUI();
};
#endif // MAINWINDOW_H
