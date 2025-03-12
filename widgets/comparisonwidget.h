#ifndef COMPARISONWIDGET_H
#define COMPARISONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QFileInfo>
#include <QPushButton>
#include <QToolButton>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QHBoxLayout>

#include "videobar.h"

class ComparisonWidget : public QWidget {
    Q_OBJECT
public:
    explicit ComparisonWidget(QWidget* parent = nullptr);
    void setCurrentDuplicate(const std::pair<std::string, std::string>& dup);
private slots:
    void onPreviousClicked();
    void onNextClicked();
    void onLeftDeleteClicked();
    void onRightDeleteClicked();
    void onIgnoreClicked();
    void onCancelClicked();
    void playVideo();
    void pauseVideo();
    void repeatVideo();
signals:
    void cancelComparison();
private:
    QToolButton* previousIconBtn;
    QToolButton* nextIconBtn;
    QLabel* infoLabel;
    std::pair<std::string, std::string> currentDuplicate;

    // Media if photo
    QLabel* leftPicLabel;
    QLabel* rightPicLabel;

    // Media if video
    QVideoWidget* leftVideoWidget;
    QVideoWidget* rightVideoWidget;
    QMediaPlayer* leftMediaPlayer;
    QMediaPlayer* rightMediaPlayer;
    QToolButton* playVideoIconBtn;
    QToolButton* pauseVideoIconBtn;
    QToolButton* repeatVideoIconBtn;
    VideoBar* leftVideoBar;
    VideoBar* rightVideoBar;

    QLabel* leftInfoLabel;
    QLabel* rightInfoLabel;
    QPushButton* leftDeleteBtn;
    QPushButton* rightDeleteBtn;
    QPushButton* ignoreBtn;
    QToolButton* cancelIconBtn;

    QHBoxLayout* mediaLayout;

    void setCurrentMedia();
    QPixmap colorSVG(const QString& path, const QColor& color);
};

#endif // COMPARISONWIDGET_H
