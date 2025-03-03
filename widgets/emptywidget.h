#ifndef EMPTYWIDGET_H
#define EMPTYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class EmptyWidget : public QWidget {
    Q_OBJECT
public:
    explicit EmptyWidget(QWidget *parent = nullptr);
signals:
    void selectDirPressed(const QString&);
private slots:
    void onDirBtnPressed();
private:
    QVBoxLayout* layout;
    QLabel* dirLabel;
    QPushButton* selectDirBtn;
};

#endif // EMPTYWIDGET_H
