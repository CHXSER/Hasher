#include "emptywidget.h"
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>

EmptyWidget::EmptyWidget(QWidget *parent)
    : QWidget{parent} {
    layout = new QVBoxLayout();
    dirLabel = new QLabel("Select a directory to analyze", this);
    dirLabel->setAlignment(Qt::AlignCenter);
    selectDirBtn = new QPushButton("Open", this);
    layout->addStretch();
    layout->addWidget(dirLabel);
    layout->addWidget(selectDirBtn, 0, Qt::AlignCenter);
    layout->addStretch();

    setLayout(layout);
    connect(selectDirBtn, &QPushButton::clicked, this, &EmptyWidget::onDirBtnPressed);
}

void EmptyWidget::onDirBtnPressed() {
    QString defaultDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Open directory"),
        defaultDir,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );
    emit selectDirPressed(dir);
}
