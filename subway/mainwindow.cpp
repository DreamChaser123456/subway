#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QQueue>
#include<math.h>
using namespace std;
typedef QPair<int,int> PII;


QVector<int> v[1000];//储存邻接点
QPoint way[10][1000];//储存每一号线的上站的编号
QMap<PII,int> mp1;//将坐标与编号连接起来
QMap<int,PII> mp2;//将编号与坐标连接起来
QMap<PII,int> mp5;//求最短路时特判
QMap<QString,int> mp3;//将名字与编号连接起来
QMap<int,QString> mp4;//将编号与名字连接起来
QMap<PII,int> line;//最短路线的标记
QMap<int,int> dot,dot1;//最短路点的标记
QMap<int,QString> way_id;
int a[1000];
int id=0;//总的点数
int id1=0,id2=0;
int func=0;
int pre[1000];//最短路时记录每个点的前一个点
int dist[1000];//bfs的时候记录每个点与起点之间的最短距离
int num[]={0,23,23,29,28,22};//每一号线的站数
int sign1[1000];
int dist1[1000];//dfs的时候求每个点与起点之间的距离，用来剪枝优化
int dist2[1000][1000];
struct node
{
    int x;
    QString s;
    bool operator <(node &h)
    {
        return x<h.x;
    }
};
QVector<node> v1;//用来记录每一条最短路径，后面根据换乘的站数排序


QString s[][33]={{},{" ","泾河","三店","码头潭公园","东吴大道","五环大道","额头湾","竹林海",
             "托洛口","古田一路","古田二路","古田三路","古田四路","汉西一路","宗关",
             "太平洋","硚口路","崇仁路","利济北路","友谊路","循礼门","大智路","三阳路",
             "黄浦路",},
             {"","天河机场","航空总部","宋家岗","巨龙大道","盘龙城","宏图大道","常青城","金银潭",
             "聂口新城","长港路","汉口火车站","新荣","王家墩东","青年路","中山公园","循礼门",
             "江汉路","积玉桥","螃蟹垭","洪山广场","中南路","宝通寺","街道口",},
             {"","屯阳大道","东风公司","体育中心","三角湖","汉阳客运站","四新大道","陶家岭","龙阳村","丹水池","宗关",
             "双墩","武汉商务区","云飞路","范湖","菱角湖","香港路","惠济二路","赵家条","罗家庄","二七小路","兴业路","后湖大道",
             "市民之家","宏图大道","黄金口","孟家铺","永安堂","玉龙路","王家湾"},
             {"","十里铺","七里庙","五里屯","汉阳火车站","钟家村","拦江路","复兴路","首义路","武昌火车站",
              "梅苑小区","虎泉","杨家湾","楚河汉界","青鱼嘴","东亭","岳家嘴","铁机路","罗家湾","园林路","仁和路","工业四路","杨春湖","武汉火车站",
              "光谷广场","车城东路","江城大道","老关村","园博中心南","园博中心北"},
             {"","前进村","建港","马鹦路","钟家村","琴台","武胜路","江正街","六渡桥","江汉路","大智路","苗素璐","香港路",
             "三眼桥","唐家墩","石桥","杨叉湖","常青花园","轻工大学","园博园北","金银湖","金银湖公园","金潭路","汉口北","塔子湖"},
             {"","中一路","竹叶山","赵家条","黄浦路","徐家棚","徐东","汪家屯","宏图大道","梨园"},
             {"","金台","施岗","阳逻开发区","阳逻","武生院","军民村","沙口","武湖","高车","青龙","谌家矶","朱家河","幸福湾","新荣客运站","百步亭花园路","后湖大道",
              "头道街","二七路","徐州新村","丹水池","新荣","惕角","藤子岗","聂口新城","汉口北","广户屯","虎泉","杨家湾","光谷广场"}};

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //设置画笔
    QPen pen(QColor(255,0,0));
     //设置画笔宽度
     pen.setWidth(2);
     painter.setPen(pen);
     painter.drawRect(20,100, 1100, 800);//矩形大小，窗口大小
     pen.setWidth(5);
     painter.setRenderHint(QPainter::Antialiasing, true);//使接下来的绘图光滑
     painter.setPen("red");
     painter.setBrush(Qt::red);
     //一号线
     int x1=150,y1=200;
     for(int i=1;i<=23;i++)
     {
         if(i>=1 && i<=4) y1+=40;
         else if(i==5) x1+=45;
         else if(i>=6 && i<=10) x1+=30,y1+=30;
         else if(i>=11 && i<=14) x1+=45;
         else if(i>=15 && i<=20) x1+=30,y1-=30;
         else y1-=40;
         way[1][i]={x1,y1};
         painter.drawEllipse(way[1][i],4,4);
         if(mp1[{way[1][i].x(),way[1][i].y()}]==0)
         {
             mp1[{way[1][i].x(),way[1][i].y()}]=++id;
             mp2[id]={way[1][i].x(),way[1][i].y()};
             way_id[id]="一号线：";
         }
     }
        //二号线
        x1=960,y1=810;
        for(int i=1;i<=23;i++)
        {
            if(i>=1 && i<=3) x1-=45;
            else if(i>=4 && i<=21) x1-=30,y1-=30;
            else if(i>=22 && i<=23) y1-=40;
            way[2][i]={x1,y1};
            painter.drawEllipse(way[2][i],4,4);
            if(mp1[{way[2][i].x(),way[2][i].y()}]==0)
            {
                mp1[{way[2][i].x(),way[2][i].y()}]=++id;
                mp2[id]={way[2][i].x(),way[2][i].y()};
                way_id[id]="二号线：";
            }
        }
     //三号线
     x1=105,y1=690;
     for(int i=1;i<=29;i++)
     {
         if(i>=1 && i<=10) x1+=30,y1-=30;
         else if(i>=11 && i<=14) x1+=45;
         else if(i>=15 && i<=17) x1+=30,y1-=30;
         else if(i>=18 && i<=22) x1+=30,y1+=30;
         else if(i>=23 && i<=26) x1+=30,y1-=30;
         else x1+=45;
         way[3][i]={x1,y1};
         painter.drawEllipse(way[3][i],4,4);
         if(mp1[{way[3][i].x(),way[3][i].y()}]==0)
         {
             mp1[{way[3][i].x(),way[3][i].y()}]=++id;
             mp2[id]={way[3][i].x(),way[3][i].y()};
             way_id[id]="三号线：";
         }
     }
     //四号线
     x1=15,y1=480;
     for(int i=1;i<=28;i++)
     {
         if(i>=1 && i<=4) x1+=45;
         else if(i>=5 && i<=14) x1+=30,y1+=30;
         else if(i>=15 && i<=18) x1+=45;
         else if(i>=19 && i<=25) x1+=30,y1-=30;
         else x1+=45;
         way[4][i]={x1,y1};
         painter.drawEllipse(way[4][i],4,4);
         if(mp1[{way[4][i].x(),way[4][i].y()}]==0)
         {
             mp1[{way[4][i].x(),way[4][i].y()}]=++id;
             mp2[id]={way[4][i].x(),way[4][i].y()};
             way_id[id]="四号线：";
         }
     }
     //五号线
     x1=165,y1=630;
     for(int i=1;i<=22;i++)
     {
         if(i>=1 && i<=6) x1+=30,y1+=30;
         else if(i>=7 && i<=15) x1+=30,y1-=30;
         else if(i>=16 && i<=19) x1-=30,y1-=30;
         else if(i==20) x1-=60,y1-=60;
         else x1-=60;
         way[5][i]={x1,y1};
         painter.drawEllipse(way[5][i],4,4);
         if(mp1[{way[5][i].x(),way[5][i].y()}]==0)
         {
             mp1[{way[5][i].x(),way[5][i].y()}]=++id;
             mp2[id]={way[5][i].x(),way[5][i].y()};
             way_id[id]="五号线：";
         }
     }

     //画线
     pen.setWidth(2);
     for(int i=1;i<=5;i++)
     {
         if(i==1) pen.setColor("blue");
         else if(i==2) pen.setColor("#aa5500");
         else if(i==3) pen.setColor("#aa00ff");
         else if(i==4) pen.setColor("green");
         else pen.setColor("orange");
         painter.setPen(pen);
         for(int j=1;j<num[i];j++)
         {
             painter.drawLine(way[i][j],way[i][j+1]);//画线
         }
     }
     //求邻接点
     for(int i=1;i<=id;i++) v[i].clear();
     for(int i=1;i<=5;i++)
     {
         for(int j=1;j<=num[i];j++)
         {
             PII l,mid,r;
             mid={way[i][j].x(),way[i][j].y()};
             if((j-1)>=1)
             {
                 l={way[i][j-1].x(),way[i][j-1].y()};
                 v[mp1[mid]].push_back(mp1[l]);
             }
             if((j+1)<=num[i])
             {
                 r={way[i][j+1].x(),way[i][j+1].y()};
                 v[mp1[mid]].push_back(mp1[r]);
             }
         }
     }
     //将可以换乘的站表示出来
     pen.setColor("black");
     pen.setWidth(7);
     painter.setPen(pen);
     painter.setBrush(Qt::black);
     for(int i=1;i<=id;i++)
     {
         if(v[i].size()>=3)
         {
             int x=mp2[i].first,y=mp2[i].second;
             painter.drawEllipse(x-2,y-2,4,4);
         }
     }
     //将每个站的标签打出来
     QFont font1("Microsoft YaHei", 5);
     painter.setFont(font1);
     painter.setPen(pen);
     for(int i=1;i<=id;i++) sign1[i]=0;
     for(int i=1;i<=5;i++)
     {
         for(int j=1;j<=num[i];j++)
         {
             PII t={way[i][j].x(),way[i][j].y()};
             int x1=mp1[t];
             if(sign1[x1]==0)
             {
                 painter.drawText(t.first+6,t.second-2,s[i][j]);
                 mp3[s[i][j]]=x1;
                 mp4[x1]=s[i][j];
                 sign1[x1]=1;
             }

         }
     }
     //画最短路的边
     for(int i=1;i<=id;i++)
     {
         for(int j=1;j<=id;j++)
         {
             if(line[{i,j}])
             {
                 QPoint begin={mp2[i].first,mp2[i].second};
                 QPoint end={mp2[j].first,mp2[j].second};
                 float x1 = begin.x();
                 float y1 = begin.y();
                 float x2 = end.x();
                 float y2 = end.y();

                 double angle = atan2(y2-y1,x2-x1);//计算线段的夹角
                 float l = 12;//箭头边的长度
                 float a = 0.6;//箭头与线段的夹角

                 int new_x1 = x2 - l * cos( angle - a);
                 int new_y1 = y2 - l * sin( angle - a);
                 int new_x2 = x2 - l * cos( angle + a);
                 int new_y2 = y2 - l * sin( angle + a);
                 QPoint l1={new_x1,new_y1};
                 QPoint r1={new_x2,new_y2};
                 pen.setWidth(4);
                 pen.setColor("red");
                 painter.setPen(pen);
                 painter.drawLine(begin,end);
                 pen.setWidth(3);
                 pen.setColor("red");
                 painter.setPen(pen);
                 painter.drawLine(l1,end);
                 painter.drawLine(r1,end);
             }
         }
     }
     //画最短路的点
     painter.setBrush(Qt::red);
     for(int i=1;i<=id;i++)
     {
         if(dot[i])
         {
             painter.drawEllipse(mp2[i].first-2,mp2[i].second-2,4,4);
         }
     }
     //画最短路中的中转站
     pen.setColor("black");
     pen.setWidth(7);
     painter.setPen(pen);
     painter.setBrush(Qt::black);
     for(int i=1;i<=id;i++)
     {
         if(dot[i] && v[i].size()>=3)
         {
             painter.drawEllipse(mp2[i].first-2,mp2[i].second-2,5,5);
         }
     }
}
//旅游观光中利用floyd求任意两点之间的最短距离
void floyd()
{
    for(int i=1;i<=id;i++)
        for(int j=1;j<=id;j++)
           dist2[i][j]=1e9;
    for(int i=1;i<=id;i++) dist2[i][i]=0;
    for(int i=1;i<=id;i++)
    {
        for(int j=1;j<=id;j++)
        {
            if(v[i].count(j)) dist2[i][j]=1;
        }
    }
    for(int k=1;k<=id;k++)
    {
        for(int i=1;i<=id;i++)
        {
            for(int j=1;j<=id;j++)
            {
                dist2[i][j]=min(dist2[i][j],dist2[i][k]+dist2[k][j]);
            }
        }
    }
}
//利用bfs求起点到终点之间的最短距离
 void bfs(int st)
 {
     memset(dist,0x3f,sizeof(dist));
     int st1[1000];
     memset(st1,0,sizeof(st1));
     dist[st]=0;
     QQueue<PII> q;
     q.push_back({0,st});
     while(q.size())
     {
         PII t=q.front();
         q.pop_front();
         int ver=t.second;
         if(st1[ver]) continue;
         st1[ver]=1;
         for(int i=0;i<v[ver].size();i++)
         {
             int j=v[ver][i];
             if(st1[j]) continue;
             if(dist[j]>dist[ver]+1)
             {
                 dist[j]=dist[ver]+1;
                 q.push_back({dist[j],j});
             }
         }
     }
 }
 //利用dfs从起点进行路径搜索，若终点为目标点，且路径长度是最短的，则输出最短路径
 void dfs(int u,int fa,int dis,int num,int ed,QString s)
 {
     if(u==ed)
     {
         s+=way_id[u];
         if(dis==dist[ed])
         {
             s+=mp4[u];
             v1.push_back({num,s});
             int x=ed;
             while(pre[x])
             {
                 line[{pre[x],x}]=1;
                 dot[x]=1;
                 x=pre[x];
             }
             dot[x]=1;
         }
         return ;
     }
     if(dist1[u]>dist[ed]) return ;
     for(int i=0;i<v[u].size();i++)
     {
         int j=v[u][i];
         if(j==fa) continue;
         if(dist1[j]>dist1[u]+1 || (dist1[j]==(dist1[u]+1) && mp5[{u,j}]==0))
         {
             pre[j]=u;
             if(dist1[j]==(dist1[u]+1)) mp5[{u,j}]=1;
             dist1[j]=dist1[u]+1;
             if(way_id[j]!=way_id[u]) dfs(j,u,dist1[j],num+1,ed,s+way_id[u]+mp4[u]+"->");
             else dfs(j,u,dist1[j],num,ed,s+way_id[u]+mp4[u]+"->");
         }
     }
 }

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("欢迎使用武汉市交通导引系统！");
    ui->listWidget->addItem("请首先选择功能：最短路或旅游观光");

}

MainWindow::~MainWindow()
{
    delete ui;
}
//计算两点之间的像素距离
double MainWindow::dis(QPoint a,QPoint b)
{
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}
//根据鼠标点击的位置和某一点的像素距离是否在一定的范围内，若在，说明鼠标点击到了某个点
int MainWindow::isin(QPoint x, QPoint y, double n)//判断鼠标光标是否点击成功（半径n的圆域范围内）
{
    //qDebug() << x << y;
    if (dis(x, y) <= n) return 1;
    else return 0;
}
//鼠标点击事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //点击了鼠标左键，就遍历所有的点，找到鼠标选择了哪个地点
    if(event->button()==Qt::LeftButton)
    {
        QPoint temp=event->pos();
        int pos=0;
        for(int i=1;i<=id;i++)
        {
            if(isin(temp,QPoint(mp2[i].first,mp2[i].second),10.0))
            {
                pos=i;
                break;
            }
        }
        if(func==1 && pos!=0)
        {
            ++id1;
            if(id1==1)
            {
                stt1=mp4[pos];
                ui->listWidget->addItem("起点-"+mp4[pos]+"添加完成");
            }
            if(id1==2)
            {
                ed1=mp4[pos];
                ui->listWidget->addItem("终点-"+mp4[pos]+"添加完成");
            }
        }
        else if(func==2 && pos!=0)
        {
            a[++id2]=pos;
            if(id2==1)
            {
                ui->listWidget->addItem("起点-"+mp4[pos]+"添加完成");
            }
            else
            {
                ui->listWidget->addItem("观光点-"+mp4[pos]+"添加完成");
            }
        }
    }
}
void MainWindow::on_pushButton_clicked()//开始搜索按钮
{
    if(id1>0)
    {
        ui->listWidget->addItem("开始搜索......");
        int st=mp3[stt1];
        int ed=mp3[ed1];
        bfs(st);
        memset(dist1,0x3f,sizeof(dist1));
        dist1[st]=0;
        dfs(st,0,0,0,ed,"");
        ui->listWidget->addItem("搜索完毕！");
        QString s1="从";
        s1+=stt1+"站";
        s1+="通往"+ed1+"站"+"所经最少站数为"+QString::number(dist[ed]+1)+"站";
        ui->listWidget->addItem(s1);
        ui->listWidget->addItem("按换乘次数非降序排序如下：");
        sort(v1.begin(),v1.end());
        for(int i=0;i<v1.size();i++)
        {
            QString s1="换乘次数为";
            s1+=QString::number(v1[i].x)+":"+v1[i].s;
            qDebug() << s1;
            ui->listWidget->addItem(s1);
        }
    }
    else
    {
        int res=1e9;
        floyd();
        int p[20]={0};
        for(int i=1;i<=id2;i++) p[i]=i;
        do
        {
            qDebug() << 11111;
            int sum=0;
            for(int i=2;i<=id2;i++) sum+=dist2[a[p[i-1]]][a[p[i]]];
            sum+=dist2[a[p[1]]][a[p[id2]]];
            res=min(res,sum);
        }while(next_permutation(p+1,p+id2+1));
        ui->listWidget->addItem("旅行路线为：");
        ui->listWidget->addItem("从"+mp4[a[1]]+"站开始观光旅游所需要乘坐的最少站数为"+QString::number(res)+"站");
        for(int i=1;i<=id2;i++) p[i]=i;
        do
        {
            int sum=0;
            for(int i=2;i<=id2;i++) sum+=dist2[a[p[i-1]]][a[p[i]]];
            sum+=dist2[a[p[1]]][a[p[id2]]];
            if(sum==res) break;
        }while(next_permutation(p+2,p+id2+1));
        for(int i=1;i<=id2;i++)
        {
            line[{a[p[i-1]],a[p[i]]}]=1;
        }
        line[{a[p[id2]],a[p[1]]}]=1;
        for(int i=2;i<=id2;i++)
        {
            ui->listWidget->addItem(mp4[a[p[i-1]]]+"->"+mp4[a[p[i]]]);
        }
        ui->listWidget->addItem(mp4[a[p[id2]]]+"->"+mp4[a[p[1]]]);
    }

    update();
}

void MainWindow::clr()
{
    for(int i=0;i<=id;i++)
    {
        stt1="";
        ed1="";
        id1=0;
        id2=0;
        line.clear();
        dot.clear();
        pre[i]=0;
        dist[i]=1e9;
        dist1[i]=1e9;
    }
    mp5.clear();
    v1.clear();
}

void MainWindow::on_pushButton_2_clicked()//刷新按钮
{
    clr();
    ui->listWidget->clear();
    update();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->listWidget->addItem("最短路功能选择成功。");
    ui->listWidget->addItem("请在地图上选择起点和终点，并点击开始搜索按钮。");
    func=1;
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget->addItem("旅游观光功能选择成功。");
    ui->listWidget->addItem("请在地图上选择起点，然后在地图中选择所要观光的景点，并点击开始搜索按钮。");
    func=2;
}
