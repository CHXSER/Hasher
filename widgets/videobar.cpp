#include "videobar.h"

VideoBar::VideoBar(QWidget *parent)
    : QWidget{parent} {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 5, 10, 5);

    currentTimeLabel = new QLabel("00:00");
    layout->addWidget(currentTimeLabel);

    progressSlider = new QSlider(Qt::Horizontal);
    progressSlider->setRange(0, 100);
    layout->addWidget(progressSlider);

    totalTimeLabel = new QLabel("00:00");
    layout->addWidget(totalTimeLabel);

    setLayout(layout);
    setFixedHeight(40);
}

void VideoBar::setDuration(qint64 duration) {
    totalDuration = duration;
    totalTimeLabel->setText(formatTime(duration));
    progressSlider->setRange(0, duration);
}

void VideoBar::updateProgress(qint64 position) {
    progressSlider->setValue(position);
    currentTimeLabel->setText(formatTime(position));
}

QSlider* VideoBar::getSlider() {
    return progressSlider;
}

QString VideoBar::formatTime(qint64 ms) {
    int seconds = ms / 1000;
    int minutes = seconds / 60;
    seconds %= 60;
    return QString::asprintf("%02d:%02d", minutes, seconds);
}
