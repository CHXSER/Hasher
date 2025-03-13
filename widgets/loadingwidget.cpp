#include "loadingwidget.h"

LoadingWidget::LoadingWidget(QWidget *parent)
    : QWidget{parent} {

    analyzingLabel = new QLabel("Analyzing: ", this);
    analyzingLabel->setAlignment(Qt::AlignCenter);
    progressBar = new QProgressBar(this);
    percentageLabel = new QLabel("0%", this);
    percentageLabel->setAlignment(Qt::AlignCenter);

    progressTextLabel = new QLabel("0 out of 0", this);
    progressTextLabel->setAlignment(Qt::AlignCenter);

    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setContentsMargins(20,20,20,20);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    mainLayout->addWidget(analyzingLabel);

    auto progressLayout = new QHBoxLayout();
    progressLayout->setSpacing(5);
    progressLayout->setAlignment(Qt::AlignCenter);

    progressLayout->addWidget(progressBar);
    progressLayout->addWidget(percentageLabel);

    mainLayout->addLayout(progressLayout);
    mainLayout->addWidget(progressTextLabel);

    setLayout(mainLayout);
}

void LoadingWidget::setDirectory(const QString& path) {
    analyzingLabel->setText("Analyzing: " + path);
}

void LoadingWidget::updateProgress(int processed, int total) {
    if (total == 0) return;
    int progress = static_cast<int>((processed / static_cast<float>(total)) * 100);

    progressBar->setValue(progress);
    percentageLabel->setText(QString::number(progress) + "%");
    progressTextLabel->setText(QString::number(processed) + " out of " + QString::number(total));
}
