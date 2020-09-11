#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.show();
    w.setFixedSize(1200,800);
    w.setWindowTitle("红黑夜法官");
    return a.exec();
}
