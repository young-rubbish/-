#include "group.h"

Group::Group(QObject *parent) : QObject(parent)
{

}
void Group::generateidentify(QWidget*aa)
{

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int u[13]={0,1,2,3,4,5,6,7,8,9,10,11,12};int i=1;int j=0;int k=0;
    while(i<=num)
    {
    QMessageBox::information(aa,"开始游戏","请一位玩家确认自己的身份与序号,其他人请闭眼！");
    int r= qrand()%num;
    r++;
    while(1)
    {if(u[r]!=0) break;
     r++;if(r>num)r=1;}
    int y=qrand()%2;
    if((y&&j<(num+1)/2)||k==num/2) {QMessageBox::information(aa,"开始游戏","您是"+QString::number(r)+"号，身份是红方");j++;a[r]=1;}
    else {QMessageBox::information(aa,"开始游戏","您是"+QString::number(r)+"号，身份是黑方");k++;a[r]=2;}
    u[r]=0;
    i++;
    }
    QMessageBox::information(aa,"开始游戏","请各位按序号就位，游戏正式开始");
}

bool Group::check(QWidget*aa)
{
    int i=1;bool flag1=0;bool flag2=0;
    while(i<=num)
    {
        if(a[i]==1) flag1=1;
        if(a[i]==2) flag2=1;
        i++;
    }
    if(flag1==0) {QMessageBox::information(aa,"游戏结束","黑方胜！");return true;}
    if(flag2==0) {QMessageBox::information(aa,"游戏结束","红方胜！");return true;}
    return false;
}

void Group::speak(QWidget*aa,int l)
{
   int i=1;
   if(l==0){
       while(i<=num){
           QMessageBox::information(aa,"发言中","现在轮到"+QString::number(i)+"号发言");i++;
       }
       return;}
   if(QMessageBox::Yes==QMessageBox::question(aa,"组织发言","村长选择发言顺序",QMessageBox::Yes|QMessageBox::No))
   {
       int i=l+1;
       while(i!=l){
           if(i>num)i=1;
           if(a[i]==0){i++;continue;}
           QMessageBox::information(aa,"发言","现在轮到"+QString::number(i)+"号发言");
           i++;
       }
   }
   else {
       int i=l-1;
       while(i!=l){
           if(i<1) i=num;
           if(a[i]==0){i--;continue;}
           QMessageBox::information(aa,"发言","现在轮到"+QString::number(i)+"号发言");
           i--;
       }
       QMessageBox::information(aa,"发言","现在轮到"+QString::number(l)+"号发言");
   }


}

bool Group::night(QWidget *aa)
{
qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
int r=qrand()%2;
if(r)QMessageBox::information(aa,"夜晚降临","今夜是红夜");
else QMessageBox::information(aa,"夜晚降临","今夜是黑夜");
QMessageBox::information(aa,"夜晚降临","请选择睁眼的玩家依次输入自己的序号，最后请输入0");
int re=0;int bl=0;
while(1)
{
int t=QInputDialog::getInt(aa,"是否守夜？","输入自己的序号",0,0,num);
if(t==0)break;
if(a[t]==0){QMessageBox::critical(aa,"是否守夜？","非法输入！请重试");continue;}
if(r){if(a[t]==1)re++;}
if(r==0){if(a[t]==2)bl++;}
}
if((r&&re%2==0)||(r==0&&bl%2==0)){QMessageBox::information(aa,"是否守夜？","下轮投票村长票数为1");return true;}
else{QMessageBox::information(aa,"是否守夜？","下轮投票村长票数正常");return false;}
}

int Group::count(QWidget*aa)
{
int i=1;int k;int j=0;int maxs[12]={0};
while(i<=num)
{vote[i]=0;i++;}
i=1;
while(i<=num)
{
    if(a[i]==0){i++;continue;}
    QMessageBox::information(aa,"投票","现在轮到"+QString::number(i)+"号玩家投票");
   while(1){
    k=QInputDialog::getInt(aa,"投票","输入被投票者的序号",1,1,num,1);
    if(a[k]) break;
    QMessageBox::critical(aa,"无效的投票","无效的投票，请重新投票");
   }
   vote[k]++;
    i++;
}
i=1;
QString O;
while(i<=num)
{
    if(a[i]==0){i++;continue;}
    int flag=0;
    O=O+QString::number(i)+"号玩家 "+QString::number(vote[i])+"\n";
    i++;
}
QMessageBox::information(aa,"投票",O);
int m=0;i=1;
while(i<=num)
{if(m<vote[i]) {m=vote[i],k=i;}i++;}
i=1;
while(i<=num)
{if(m==vote[i]){maxs[j]=i;j++;}i++;}
if(j==1){return k;}
i=1;
QString A=QString::number(maxs[0]);
while(i<j)
{A=A+"、"+QString::number(maxs[i]);i++;}
QMessageBox::information(aa,"投票",A+"号玩家得票最高且相同,需对他们重新投票");
return count(aa,maxs,j);
}

int Group::count(QWidget *aa, int *maxs, int j)
{
    int i=0;int k;int ma[12];int l=0;
    while(i<j)
    {vote[maxs[i]]=0;i++;}
    i=1;
    while(i<=num)
    {
        while(a[i]==0){i++;continue;}
        QMessageBox::information(aa,"投票","现在轮到"+QString::number(i)+"号玩家投票");
       while(1){
        k=QInputDialog::getInt(aa,"投票","输入被投票者的序号",1,1,num,1);
        int flag=0;
        for(int i=0;i<j;i++)
        {if(k==maxs[i])flag=1;}
        if(flag)break;
        QMessageBox::critical(aa,"无效的投票","无效的投票，请重新投票");
       }
       vote[k]++;
        i++;
    }
    i=0;
    QString O;
    while(i<j)
    {
        O=O+QString::number(maxs[i])+"号玩家 "+QString::number(vote[maxs[i]])+"\n";
        i++;
    }
    QMessageBox::information(aa,"本轮投票情况",O);
    int m=0;i=0;
    while(i<j)
    {if(m<vote[maxs[i]]) {m=vote[maxs[i]],k=maxs[i];}i++;}
    i=0;
    while(i<j)
    {if(m==vote[maxs[i]]){ma[l]=maxs[i];l++;}i++;}
    if(l==1){return k;}
    i=1;
    QString A=QString::number(ma[0]);
    while(i<l)
    {A=A+"、"+QString::number(ma[i]);i++;}
    QMessageBox::information(aa,"投票",A+"号玩家得票最高且相同,需对他们重新投票");
    return count(aa,ma,l);
}

int Group::count1(QWidget *aa)
{
    int i=1;int k;int j=0;int maxs[12]={0};
    while(i<=num)
    {vote[i]=0;i++;}
    i=1;
    while(i<=num)
    {
        while(a[i]==0){i++;continue;}
        QMessageBox::information(aa,"投票","现在轮到"+QString::number(i)+"号玩家投票");
       while(1){
        k=QInputDialog::getInt(aa,"投票","输入被投票者的序号",1,1,num,1);
        if(a[k]) break;
        QMessageBox::critical(aa,"无效的投票","无效的投票，请重新投票");
       }
       if(i==head){if(h) vote[k]++;else vote[k]+=3;}
       else vote[k]+=2;
       i++;
    }
    i=1;
    QString O;
    while(i<=num)
    {
        if(a[i]==0){i++;continue;}
        if(vote[i]%2)O=O+QString::number(i)+"号玩家 "+QString::number(vote[i]/2)+".5\n";
        else O=O+QString::number(i)+"号玩家 "+QString::number(vote[i]/2)+"\n";
        i++;
    }
    QMessageBox::information(aa,"投票",O);
    int m=0;i=1;
    while(i<=num)
    {if(m<vote[i]) {m=vote[i],k=i;}i++;}
    i=1;
    while(i<=num)
    {if(m==vote[i]){maxs[j]=i;j++;}i++;}
    if(j==1){return k;}
    i=1;
    QString A=QString::number(maxs[0]);
    while(i<j)
    {A=A+"、"+QString::number(maxs[i]);i++;}
    QMessageBox::information(aa,"投票",A+"号玩家得票最高且相同,需对他们重新投票");
    return count1(aa,maxs,j);
}

Group::count1(QWidget *aa, int *maxs, int j)
{
    int i=0;int k;int ma[12];int l=0;
    while(i<j)
    {vote[maxs[i]]=0;i++;}
    i=1;
    while(i<=num)
    {
        while(a[i]==0){i++;continue;}
        QMessageBox::information(aa,"投票","现在轮到"+QString::number(i)+"号玩家投票");
       while(1){
        k=QInputDialog::getInt(aa,"投票","输入被投票者的序号",1,1,num,1);
        int flag=0;
        for(int i=0;i<j;i++)
        {if(k==maxs[i])flag=1;}
        if(flag)break;
        QMessageBox::critical(aa,"无效的投票","无效的投票，请重新投票");
       }
       if(i==head){if(h) vote[k]++;else vote[k]+=3;}
       else vote[k]+=2;
       i++;
    }
    i=0;
    QString O;
    while(i<j)
    {
        O=O+QString::number(maxs[i])+"号玩家 "+QString::number(vote[maxs[i]])+"\n";
        i++;
    }
    QMessageBox::information(aa,"本轮投票情况",O);
    int m=0;i=0;
    while(i<j)
    {if(m<vote[maxs[i]]) {m=vote[maxs[i]],k=maxs[i];}i++;}
    i=0;
    while(i<j)
    {if(m==vote[maxs[i]]){ma[l]=maxs[i];l++;}i++;}
    if(l==1){return k;}
    i=1;
    QString A=QString::number(ma[0]);
    while(i<l)
    {A=A+"、"+QString::number(ma[i]);i++;}
    QMessageBox::information(aa,"投票",A+"号玩家得票最高且相同,需对他们重新投票");
    return count(aa,ma,l);
}

void Group::kick(QWidget*aa,int l)
{
    h=!h;
    if(a[l]==1)QMessageBox::information(aa,"玩家死亡",QString::number(l)+"号玩家死亡，身份是红方");
    else QMessageBox::information(aa,"玩家死亡",QString::number(l)+"号玩家死亡，身份是黑方");
    a[l]=0;
    if(l==head) {QMessageBox::information(aa,"村长死亡","请选择一人接替村长");
    while(1){int head=QInputDialog::getInt(aa,"接任村长","输入下一任村长的序号",1,1,num);
        if(a[head]==0){QMessageBox::critical(aa,"非法输入","非法输入，请重试！");continue;}
        break;
  }
    }
}
