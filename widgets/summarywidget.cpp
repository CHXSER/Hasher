#include "summarywidget.h"

SummaryWidget::SummaryWidget(QWidget *parent)
    : QWidget{parent} {
    auto* layout = new QVBoxLayout();
    summaryLabel = new QLabel("Summary: ", this);
    listFiles = new QLabel("", this);
    numberFiles = new QLabel("", this);
    cancelBtn = new QPushButton("Cancel", this);
    confirmBtn = new QPushButton("Confirm", this);

    summaryLabel->setAlignment(Qt::AlignCenter);
    listFiles->setAlignment(Qt::AlignCenter);
    numberFiles->setAlignment(Qt::AlignCenter);

    layout->addStretch();
    layout->addWidget(summaryLabel);
    layout->addWidget(numberFiles);
    layout->addWidget(listFiles);

    auto* hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(cancelBtn);
    hLayout->addWidget(confirmBtn);
    hLayout->addStretch();

    layout->addLayout(hLayout);
    layout->addStretch();

    setLayout(layout);
    connect(cancelBtn, &QPushButton::clicked, this, &SummaryWidget::onCancelClicked);
    connect(confirmBtn, &QPushButton::clicked, this, &SummaryWidget::onConfirmClicked);
}

void SummaryWidget::setDeleteList(const QList<QString> &deleteList) {
    this->deleteList = deleteList;
    numberFiles->clear();
    numberFiles->setText("Number of operations: " + QString::number(deleteList.size()));

    QStringList fileNames;
    int index = 1;
    for (const auto& file : deleteList) {
        fileNames.append(QString::number(index++) + ". " + file);
    }

    listFiles->setText(fileNames.join("\n"));
}

void SummaryWidget::setIgnoreList(const QList<std::pair<std::string, std::string>>& ignoreList) {
    this->ignoreList = ignoreList;
}


void SummaryWidget::onCancelClicked() {
    emit cancel();
}

void SummaryWidget::onConfirmClicked() {
    emit complete();
}
