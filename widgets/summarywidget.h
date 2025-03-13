#ifndef SUMMARYWIDGET_H
#define SUMMARYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class SummaryWidget : public QWidget {
    Q_OBJECT
public:
    explicit SummaryWidget(QWidget *parent = nullptr);
    void setDeleteList(const QList<QString>& deleteList);
    void setIgnoreList(const QList<std::pair<std::string, std::string>>& ignoreList);
signals:
    void complete();
    void cancel();

private slots:
    void onCancelClicked();
    void onConfirmClicked();
private:
    QLabel* summaryLabel;
    QLabel* listFiles;
    QLabel* numberFiles;
    QPushButton* cancelBtn;
    QPushButton* confirmBtn;

    QList<QString> deleteList;
    QList<std::pair<std::string, std::string>> ignoreList;
};

#endif // SUMMARYWIDGET_H
