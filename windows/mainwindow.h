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
#include "../widgets/summarywidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDirSelect(const QString& dir);
    void onQueueDelete(const QString& filePath);
    void onQueueIgnore(const std::pair<std::string, std::string>& dup);
private:
    QStackedWidget* stackedWidget;
    EmptyWidget* emptyWidget;
    ComparisonWidget* comparisonWidget;
    LoadingWidget* loadingWidget;
    DuplicateManager* duplicateManager;
    SummaryWidget* summaryWidget;
    std::unique_ptr<MediaProcessor> mediaProcessor;
    std::vector<std::pair<std::string, std::string>> duplicates;
    QList<QString> filesToDelete;
    QList<std::pair<std::string, std::string>> pairsToIgnore;
    int currentDupIndex;
    void updateUI();
};
#endif // MAINWINDOW_H
