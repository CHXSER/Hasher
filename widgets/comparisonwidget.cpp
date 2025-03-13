#include "comparisonwidget.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QApplication>
#include <QImageReader>

ComparisonWidget::ComparisonWidget(QWidget *parent)
    : QWidget(parent) {
    // Setting icon color
    QColor color = QApplication::palette().color(QPalette::Text);

    QPixmap backwardPixmap = colorSVG("../../icons/backward.svg", color);
    QPixmap forwardPixmap  = colorSVG("../../icons/forward.svg", color);
    QPixmap xmarkPixmap    = colorSVG("../../icons/xmark.svg", color);
    QPixmap playPixmap     = colorSVG("../../icons/play.svg", color);
    QPixmap pausePixmap    = colorSVG("../../icons/pause.svg", color);
    QPixmap repeatPixmap   = colorSVG("../../icons/repeat.svg", color);

    previousIconBtn = new QToolButton(this);
    previousIconBtn->setIcon(QIcon(backwardPixmap));
    infoNumberLabel = new QLabel(this);
    nextIconBtn = new QToolButton(this);
    nextIconBtn->setIcon(QIcon(forwardPixmap));
    infoLabel = new QLabel(this);

    leftInfoLabel = new QLabel(this);
    rightInfoLabel = new QLabel(this);
    leftDeleteBtn = new QPushButton("Delete", this);
    rightDeleteBtn = new QPushButton("Delete", this);
    ignoreBtn = new QPushButton("Ignore", this);
    cancelIconBtn = new QToolButton(this);
    cancelIconBtn->setIcon(QIcon(xmarkPixmap));

    leftVideoWidget = new QVideoWidget(this);
    rightVideoWidget = new QVideoWidget(this);
    leftMediaPlayer = new QMediaPlayer(this);
    rightMediaPlayer = new QMediaPlayer(this);
    leftPicLabel = new QLabel(this);
    rightPicLabel = new QLabel(this);
    playVideoIconBtn = new QToolButton(this);
    playVideoIconBtn->setIcon(QIcon(playPixmap));
    pauseVideoIconBtn = new QToolButton(this);
    pauseVideoIconBtn->setIcon(QIcon(pausePixmap));
    repeatVideoIconBtn = new QToolButton(this);
    repeatVideoIconBtn->setIcon(QIcon(repeatPixmap));
    leftVideoBar = new VideoBar(this);
    rightVideoBar = new VideoBar(this);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* topLayout = new QHBoxLayout();
    QWidget* topWidget = new QWidget();
    QHBoxLayout* fileInfoLayout = new QHBoxLayout();
    QWidget* fileInfoWidget = new QWidget();
    mediaLayout = new QHBoxLayout();
    QWidget* mediaWidget = new QWidget();
    QHBoxLayout* btnLayout1 = new QHBoxLayout();
    QWidget* btnWidget1 = new QWidget();
    QHBoxLayout* btnLayout2 = new QHBoxLayout();
    QWidget* btnWidget2 = new QWidget();

    topLayout->addWidget(previousIconBtn);
    topLayout->addStretch();
    topLayout->addWidget(infoNumberLabel);
    topLayout->addStretch();
    topLayout->addWidget(nextIconBtn);
    topWidget->setLayout(topLayout);

    fileInfoLayout->addWidget(leftInfoLabel);
    fileInfoLayout->addStretch();
    fileInfoLayout->addWidget(rightInfoLabel);
    fileInfoWidget->setLayout(fileInfoLayout);

    mediaWidget->setLayout(mediaLayout);

    btnLayout1->addWidget(leftDeleteBtn);
    btnLayout1->addWidget(rightDeleteBtn);
    btnWidget1->setLayout(btnLayout1);

    btnLayout2->addWidget(ignoreBtn);
    btnLayout2->addWidget(cancelIconBtn);
    btnWidget2->setLayout(btnLayout2);

    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(fileInfoWidget);
    mainLayout->addWidget(mediaWidget);
    mainLayout->addWidget(btnWidget1);
    mainLayout->addWidget(btnWidget2);
    setLayout(mainLayout);

    connect(previousIconBtn, &QToolButton::clicked, this, &ComparisonWidget::onPreviousClicked);
    connect(nextIconBtn, &QToolButton::clicked, this, &ComparisonWidget::onNextClicked);
    connect(playVideoIconBtn, &QToolButton::clicked, this, &ComparisonWidget::playVideo);
    connect(pauseVideoIconBtn, &QToolButton::clicked, this, &ComparisonWidget::pauseVideo);
    connect(repeatVideoIconBtn, &QToolButton::clicked, this, &ComparisonWidget::repeatVideo);
    connect(leftDeleteBtn, &QPushButton::clicked, this, &ComparisonWidget::onLeftDeleteClicked);
    connect(rightDeleteBtn, &QPushButton::clicked, this, &ComparisonWidget::onRightDeleteClicked);
    connect(ignoreBtn, &QPushButton::clicked, this, &ComparisonWidget::onIgnoreClicked);
    connect(cancelIconBtn, &QToolButton::clicked, this, &ComparisonWidget::onCancelClicked);
}

void ComparisonWidget::setCurrentDuplicate(const std::pair<std::string, std::string>& dup) {
    currentDuplicate = dup;
    setCurrentMedia();
}

void ComparisonWidget::setDupLabel(int current, int max) {
    infoNumberLabel->setText("Duplicate n " + QString::number(current) + " out of " + QString::number(max));
}

void ComparisonWidget::onPreviousClicked() {
    emit previousComparison();
}

void ComparisonWidget::onNextClicked() {
    emit nextComparison();
}

void ComparisonWidget::onLeftDeleteClicked() {

}

void ComparisonWidget::onRightDeleteClicked() {

}

void ComparisonWidget::onIgnoreClicked() {
    onNextClicked();
}

void ComparisonWidget::onCancelClicked() {
    emit cancelComparison();
}

void ComparisonWidget::playVideo() {
    leftMediaPlayer->play();
    rightMediaPlayer->play();
}

void ComparisonWidget::pauseVideo() {
    leftMediaPlayer->pause();
    rightMediaPlayer->pause();
}

void ComparisonWidget::repeatVideo() {
    leftMediaPlayer->setPosition(0);
    rightMediaPlayer->setPosition(0);
    leftMediaPlayer->play();
    rightMediaPlayer->play();
}

void ComparisonWidget::setCurrentMedia() {
    QFileInfo fileInfo1(QString::fromStdString(currentDuplicate.first));
    QFileInfo fileInfo2(QString::fromStdString(currentDuplicate.second));
    auto extension1 = fileInfo1.suffix().toLower();
    auto extension2 = fileInfo2.suffix().toLower();
    QUrl fileFirstUrl(QString::fromStdString(currentDuplicate.first));
    QUrl fileSecondUrl(QString::fromStdString(currentDuplicate.second));

    QLayoutItem* item;
    while ((item = mediaLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if ((extension1 == "mp4" || extension1 == "webm" || extension1 == "gif") &&
        (extension2 == "mp4" || extension2 == "webm" || extension2 == "gif") ) {

        // Hide images
        leftPicLabel->hide();
        rightPicLabel->hide();
        // Show video
        leftVideoWidget->show();
        rightVideoWidget->show();
        playVideoIconBtn->show();
        pauseVideoIconBtn->show();
        repeatVideoIconBtn->show();
        leftVideoBar->show();
        rightVideoBar->show();

        leftVideoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        rightVideoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        leftMediaPlayer->setSource(fileFirstUrl);
        leftMediaPlayer->setVideoOutput(leftVideoWidget);
        rightMediaPlayer->setSource(fileSecondUrl);
        rightMediaPlayer->setVideoOutput(rightVideoWidget);

        connect(leftMediaPlayer, &QMediaPlayer::durationChanged, leftVideoBar, &VideoBar::setDuration);
        connect(leftMediaPlayer, &QMediaPlayer::positionChanged, leftVideoBar, &VideoBar::updateProgress);
        connect(leftVideoBar->getSlider(), &QSlider::sliderMoved, leftMediaPlayer, &QMediaPlayer::setPosition);

        connect(rightMediaPlayer, &QMediaPlayer::durationChanged, rightVideoBar, &VideoBar::setDuration);
        connect(rightMediaPlayer, &QMediaPlayer::positionChanged, rightVideoBar, &VideoBar::updateProgress);
        connect(rightVideoBar->getSlider(), &QSlider::sliderMoved, rightMediaPlayer, &QMediaPlayer::setPosition);

        auto leftVideoLayout = new QVBoxLayout();
        leftVideoLayout->addWidget(leftVideoWidget);
        leftVideoLayout->addWidget(leftVideoBar);

        auto rightVideoLayout = new QVBoxLayout();
        rightVideoLayout->addWidget(rightVideoWidget);
        rightVideoLayout->addWidget(rightVideoBar);

        playVideoIconBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        pauseVideoIconBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        repeatVideoIconBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QVBoxLayout* controlsLayout = new QVBoxLayout();
        controlsLayout->addWidget(playVideoIconBtn);
        controlsLayout->addWidget(pauseVideoIconBtn);
        controlsLayout->addWidget(repeatVideoIconBtn);

        mediaLayout->addLayout(leftVideoLayout, 1);
        mediaLayout->addLayout(controlsLayout);
        mediaLayout->addLayout(rightVideoLayout, 1);
    } else if ((extension1 == "jpg" || extension1 == "png" || extension1 == "jpeg") &&
        (extension2 == "jpg" || extension2 == "png" || extension2 == "jpeg")) {
        // Hide videos
        leftVideoWidget->hide();
        rightVideoWidget->hide();
        playVideoIconBtn->hide();
        pauseVideoIconBtn->hide();
        repeatVideoIconBtn->hide();
        leftVideoBar->hide();
        rightVideoBar->hide();
        // Show images
        leftPicLabel->show();
        rightPicLabel->show();

        QImage leftPix(QString::fromStdString(currentDuplicate.first));
        QImage rightPix(QString::fromStdString(currentDuplicate.second));


        leftPicLabel->setPixmap(QPixmap::fromImage(leftPix));
        rightPicLabel->setPixmap(QPixmap::fromImage(rightPix));

        auto* leftImageLayout = new QVBoxLayout();
        leftImageLayout->addWidget(leftPicLabel);
        leftImageLayout->addStretch();
        auto* rightImageLayout = new QVBoxLayout();
        rightImageLayout->addWidget(rightPicLabel);
        rightImageLayout->addStretch();

        mediaLayout->addLayout(leftImageLayout);
        mediaLayout->addStretch();
        mediaLayout->addLayout(rightImageLayout);
    }
    leftInfoLabel->setText(fileInfo1.fileName() + ", Size: " + QString::number(fileInfo1.size()));
    rightInfoLabel->setText(fileInfo2.fileName() + ", Size: " + QString::number(fileInfo2.size()));
    update();
}

QPixmap ComparisonWidget::colorSVG(const QString& path, const QColor& color) {
    QPixmap pixmap(path);
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), color);
    painter.end();
    return pixmap;
}
