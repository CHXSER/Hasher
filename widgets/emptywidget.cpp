#include "emptywidget.h"
#include <QFileDialog>

EmptyWidget::EmptyWidget(QWidget *parent)
    : QWidget{parent} {
    layout = new QVBoxLayout(this);
    dirLabel = new QLabel("Select a directory to analyze", this);
    selectDirBtn = new QPushButton("Open", this);
    layout->addWidget(dirLabel);
    layout->addWidget(selectDirBtn);

    connect(selectDirBtn, &QPushButton::clicked, this, &EmptyWidget::onDirBtnPressed);
}

void EmptyWidget::onDirBtnPressed() {
    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Open directory"),
        "/home",
        QFileDialog::ShowDirsOnly
    );
    emit selectDirPressed(dir);
}
