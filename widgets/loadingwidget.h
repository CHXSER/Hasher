#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>

class LoadingWidget : public QWidget {
    Q_OBJECT
public:
    explicit LoadingWidget(QWidget *parent = nullptr);
    void setDirectory(const QString& path);
    void updateProgress(int processed, int total);

private:
    QLabel* analyzingLabel;
    QProgressBar* progressBar;
    QLabel* percentageLabel;
    QLabel* progressTextLabel;
};

#endif // LOADINGWIDGET_H
