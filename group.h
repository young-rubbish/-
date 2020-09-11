#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QTime>
#include <QtGlobal>
#include <QMessageBox>
#include <qinputdialog.h>
class Group : public QObject
{
    Q_OBJECT
    int num;
    int head=0;
    int a[13];
    int vote[13];
    bool h;
public:
    explicit Group(QObject *parent = nullptr);
    void setnumandh(int l){num=l;h=num%2;}
    void speak(QWidget*aa, int l=0);
    bool night(QWidget*aa);
    int count(QWidget*aa);
    int count(QWidget *aa,int*maxs,int j);
    int count1(QWidget*aa);
    count1(QWidget *aa,int*maxs,int j);
    void kick(QWidget *aa, int l);
    void generateidentify(QWidget*aa);
    void sethead(int n){head=n;}
    void gethead(int n){n=head;}
    bool check(QWidget *aa);
    ~Group(){}
signals:

public slots:

};

#endif // GROUP_H
