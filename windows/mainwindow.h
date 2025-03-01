#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>

#include "../models/mediaprocessor.h"
#include "../models/duplicatemanager.h"

#include "../widgets/emptywidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDirSelect();

private:
    QStackedWidget* stackedWidget;
    EmptyWidget* emptyWidget;
    MediaProcessor* mediaProcessor;
    DuplicateManager* duplicateManager;
    void updateUI();
};
#endif // MAINWINDOW_H
