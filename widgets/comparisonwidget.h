#ifndef COMPARISONWIDGET_H
#define COMPARISONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVideoWidget>
#include <QMediaPlayer>

class ComparisonWidget : public QWidget {
    Q_OBJECT
public:
    explicit ComparisonWidget(QWidget *parent = nullptr);
    void setMedia(const QString&, const QString&);
signals:
    void deleteFFile();
    void deleteSFile();
    void ignore();
private slots:
    void onDeleteFFile();
    void onDeleteSFile();
    void onIgnore();
private:
    QLabel* firstFileLabel;
    QLabel* secondFileLabel;
    QVideoWidget* firstVideoWidget;
    QVideoWidget* secondVideoWidget;
    QMediaPlayer* firstMediaPlayer;
    QMediaPlayer* secondMediaPlayer;
    QPushButton* deleteFirstFile;
    QPushButton* deleteSecondFile;
    QPushButton* ignoreButton;
    void setupUI();
    void displayMedia(const QString& filePath, QLabel* label,
                      QVideoWidget* videoWidget, QMediaPlayer* player);
};

#endif // COMPARISONWIDGET_H
