#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btn= new QPushButton("开始游戏",this);
    btn->setFixedSize(200,50);
    btn->move(500,730);
    player=new Group;
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(slotStart()));


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    int i=0;
    QPainter p(this);
    while(i<2)
    {
        int j=0;
        while(j<6)
        {
            if(s[i][j]==0){p.setBrush(Qt::gray);p.drawRect(30+200*j,30+360*i,140,100);}
            else if(s[i][j]==1){
                p.setBrush(Qt::blue);
                p.drawRect(30+200*j,30+360*i,140,100);
                p.drawText(QRect(30+200*j,30+360*i,140,100),QString::number(i*6+j+1),QTextOption(Qt::AlignCenter));
                }
            else if(s[i][j]==2){
                p.setBrush(Qt::red);
                p.drawRect(30+200*j,30+360*i,140,100);
                p.drawText(QRect(30+200*j,30+360*i,140,100),QString::number(i*6+j+1),QTextOption(Qt::AlignCenter));}
            else if(s[i][j]==3){
                p.setBrush(Qt::black);
                p.drawRect(30+200*j,30+360*i,140,100);
                p.drawText(QRect(30+200*j,30+360*i,140,100),QString::number(i*6+j),QTextOption(Qt::AlignCenter));}
            j++;
        }
        i++;
    }
}
void MainWindow::slotStart()
{
    btn->setText("重新开始");
    int i=0;
    while(i<2){
        int j=0;
        while(j<6)
        {
            s[i][j]=0;
            j++;
        }i++;
    }
    i=0;int j=0;
    number=QInputDialog::getInt(this,"开始游戏","请输入玩家人数（4~12人）",4,4,12,1);
    while(i*6+j<number)
    {
        s[i][j]=1;
        j++;
        if(j==6){j=0;i++;}
    }
        player->setnumandh(number);
        player->generateidentify(this);
        player->speak(this);
        QMessageBox::information(this,"投票","现在开始选举村长");
        int max=player->count(this);
        QMessageBox::information(this,"投票",QString::number(max)+"号玩家当选村长");
        player->sethead(max);
        while(1)
        {
            bool t=player->night(this);
            QMessageBox::information(this,"天亮","天亮了，村长组织发言");
            player->gethead(max);
            player->speak(this,max);
            QMessageBox::information(this,"投票","现在投票决定淘汰一名玩家");
            int die;
            if(t)die=player->count(this);
            else die=player->count1(this);
            player->kick(this,die);
            t=player->check(this);
        }

}
