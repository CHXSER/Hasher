#include "comparisonwidget.h"

#include <QVBoxLayout>

ComparisonWidget::ComparisonWidget(QWidget *parent)
    : QWidget(parent) {
    previousIconBtn = new QToolButton(this);
    nextIconBtn = new QToolButton(this);
    infoLabel = new QLabel(this);

    leftInfoLabel = new QLabel(this);
    rightInfoLabel = new QLabel(this);
    leftDeleteBtn = new QPushButton("Delete", this);
    rightDeleteBtn = new QPushButton("Delete", this);
    ignoreBtn = new QPushButton("Ignore", this);
    cancelIconBtn = new QToolButton(this);

    leftVideoWidget = new QVideoWidget(this);
    rightVideoWidget = new QVideoWidget(this);
    leftMediaPlayer = new QMediaPlayer(this);
    rightMediaPlayer = new QMediaPlayer(this);
    leftPicLabel = new QLabel(this);
    rightPicLabel = new QLabel(this);

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

    connect(previousIconBtn, &QToolButton::triggered, this, &ComparisonWidget::onPreviousClicked);
    connect(nextIconBtn, &QToolButton::triggered, this, &ComparisonWidget::onNextClicked);
    connect(leftDeleteBtn, &QPushButton::clicked, this, &ComparisonWidget::onLeftDeleteClicked);
    connect(rightDeleteBtn, &QPushButton::clicked, this, &ComparisonWidget::onRightDeleteClicked);
    connect(ignoreBtn, &QPushButton::clicked, this, &ComparisonWidget::onIgnoreClicked);
    connect(cancelIconBtn, &QToolButton::triggered, this, &ComparisonWidget::onCancelClicked);
}

void ComparisonWidget::setCurrentDuplicate(const std::pair<std::string, std::string>& dup) {
    currentDuplicate = dup;
    setCurrentMedia();
}

void ComparisonWidget::onPreviousClicked() {

}

void ComparisonWidget::onNextClicked()
{

}

void ComparisonWidget::onLeftDeleteClicked()
{

}

void ComparisonWidget::onRightDeleteClicked()
{

}

void ComparisonWidget::onIgnoreClicked()
{

}

void ComparisonWidget::onCancelClicked() {
    emit cancelComparison();
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

        leftVideoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        rightVideoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        leftMediaPlayer->setSource(fileFirstUrl);
        leftMediaPlayer->setVideoOutput(leftVideoWidget);
        rightMediaPlayer->setSource(fileSecondUrl);
        rightMediaPlayer->setVideoOutput(rightVideoWidget);

        mediaLayout->addWidget(leftVideoWidget, 1);
        mediaLayout->addSpacing(20);
        mediaLayout->addWidget(rightVideoWidget, 1);

        leftMediaPlayer->play();
        rightMediaPlayer->play();

    } else if ((extension1 == "jpg" || extension1 == "png" || extension1 == "jpeg") &&
        (extension2 == "jpg" || extension2 == "png" || extension2 == "jpeg")) {
            QPixmap leftPix(QString::fromStdString(currentDuplicate.first));
            QPixmap rightPix(QString::fromStdString(currentDuplicate.second));

            leftPicLabel->setPixmap(leftPix);
            rightPicLabel->setPixmap(rightPix);

            mediaLayout->addWidget(leftPicLabel);
            mediaLayout->addStretch();
            mediaLayout->addWidget(rightPicLabel);
    }
    leftInfoLabel->setText(fileInfo1.fileName() + ", Size: " + QString::number(fileInfo1.size()));
    rightInfoLabel->setText(fileInfo2.fileName() + ", Size: " + QString::number(fileInfo2.size()));
}
