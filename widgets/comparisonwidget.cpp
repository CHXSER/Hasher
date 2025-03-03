#include "comparisonwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileInfo>

ComparisonWidget::ComparisonWidget(QWidget *parent)
    : QWidget{parent} {
    setupUI();
}

void ComparisonWidget::setMedia(const QString& fFile, const QString& sFile) {
    displayMedia(fFile, firstFileLabel, firstVideoWidget, firstMediaPlayer);
    displayMedia(sFile, secondFileLabel, secondVideoWidget, secondMediaPlayer);
}

void ComparisonWidget::setupUI() {
    auto mediaLayout = new QHBoxLayout();
    auto btnLayout = new QVBoxLayout();
    auto mainLayout = new QVBoxLayout(this);

    firstFileLabel = new QLabel(this);
    secondFileLabel = new QLabel(this);
    firstVideoWidget = new QVideoWidget(this);
    secondVideoWidget = new QVideoWidget(this);
    firstMediaPlayer = new QMediaPlayer(this);
    secondMediaPlayer = new QMediaPlayer(this);

    firstMediaPlayer->setVideoOutput(firstVideoWidget);
    secondMediaPlayer->setVideoOutput(secondVideoWidget);

    mediaLayout->addWidget(firstFileLabel);
    mediaLayout->addWidget(firstVideoWidget);
    mediaLayout->addWidget(secondFileLabel);
    mediaLayout->addWidget(secondVideoWidget);

    deleteFirstFile = new QPushButton("Delete", this);
    deleteSecondFile = new QPushButton("Delete", this);
    ignoreButton = new QPushButton("Ignore", this);

    btnLayout->addWidget(deleteFirstFile);
    btnLayout->addWidget(deleteSecondFile);
    btnLayout->addWidget(ignoreButton);

    mainLayout->addLayout(mediaLayout);
    mainLayout->addLayout(btnLayout);

    connect(deleteFirstFile, &QPushButton::clicked, this, &ComparisonWidget::onDeleteFFile);
    connect(deleteSecondFile, &QPushButton::clicked, this, &ComparisonWidget::onDeleteSFile);
    connect(ignoreButton, &QPushButton::clicked, this, &ComparisonWidget::onIgnore);
}

void ComparisonWidget::onDeleteFFile() {
    emit deleteFFile();
}

void ComparisonWidget::onDeleteSFile() {
    emit deleteSFile();
}

void ComparisonWidget::onIgnore() {
    emit ignore();
}

void ComparisonWidget::displayMedia(const QString &filePath, QLabel *label,
                                    QVideoWidget *videoWidget, QMediaPlayer *player) {
    QFileInfo fileInfo(filePath);
    QString extension = fileInfo.suffix().toLower();

    if (extension == "mp4" || extension == "gif" || extension == "webm") {
        label->hide();
        videoWidget->show();
        player->setSource(QUrl::fromLocalFile(filePath));
        player->play();
    } else if (extension == "jpg" || extension == "png" || extension == "jpeg") {
        videoWidget->hide();
        label->setPixmap(QPixmap(filePath).scaled(400, 400, Qt::KeepAspectRatio));
        label->show();
    }
}
