#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <group.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int s[2][6]={{0},{0}};
    void paintEvent(QPaintEvent*);
    QPushButton*btn,*btn1;
    Group *player;
    int number;

public slots:
    void slotStart();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
