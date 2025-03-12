#ifndef VIDEOBAR_H
#define VIDEOBAR_H

#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>

class VideoBar : public QWidget {
    Q_OBJECT
public:
    explicit VideoBar(QWidget *parent = nullptr);
    void setDuration(qint64 duration);
    void updateProgress(qint64 position);
    QSlider* getSlider();
private:
    QLabel* currentTimeLabel;
    QLabel* totalTimeLabel;
    QSlider* progressSlider;
    qint64 totalDuration;
    QString formatTime(qint64 ms);
};

#endif // VIDEOBAR_H
