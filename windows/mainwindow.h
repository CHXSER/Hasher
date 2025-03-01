#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>

#include "../models/mediaprocessor.h"
#include "../models/duplicatemanager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectDir();
    void onDeleteFBtn();
    void onDeleteSBtn();
    void onIgnoreBtn();

private:
    QPushButton* selectDirBtn;
    QPushButton* deleteFDupBtn;
    QPushButton* deleteSDupBtn;
    QPushButton* ignoreDupBtn;
    QPushButton* nextDupBtn;
    QLabel* mediaFLabel;
    QLabel* mediaSLabel;
    QStackedWidget* stackedWidget;
    MediaProcessor* mediaProcessor;
    DuplicateManager* duplicateManager;
    void updateUI();
    void setupConnections();
};
#endif // MAINWINDOW_H
