#include "windows/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("Hasher");
    MainWindow w;
    w.show();
    return a.exec();
}
