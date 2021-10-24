#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsLineItem>
#include <QListView>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QVector>
#include <QMouseEvent>
#include <QDialog>
#include <QPixmap>
#include <QGridLayout>
#include <QTime>
#include <QElapsedTimer>
#include <QLineEdit>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QtGlobal>
#include <QRandomGenerator>
#include "insidewidget.h"

//#include "findShortestPath.h"
//#include "mapwidget.h"

extern QElapsedTimer find_time;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createToolBar();
    void createAction();
    void setStart(int X, int Y);
    void setEnd(int X, int Y);
    void setMid(int X, int Y);
    void setNextPos (int index);
    void setTmp(int X, int Y);
    //void initScene();
    void initMainWindow();
    void printLog(const QString& s);//打印日志
    int timeChange();
    QString printTime(int i);
    void Delay_MSec(unsigned int msec);
    void screenLog(const QString& s);//在browser上打印日志
    void aroundBuilding(int num);
    void congestionControl();
    void ifS4();
    //void leastTimeMode();

public slots:

    void paintPath();
    void navigation();
    void clear();
    void control();
    void multiFind();
    void setStartStation();
    void setMidStation();
    void setEndStation();
    void paintLog();//单独打印日志
    void paintAni();//单独绘制路线
    void leastTimeMode();
    //void changeUser();
    //void revise();
    //void callOtherMap();
    //void showDialog();

signals:
    void aniSignal();//日志打印结束后触发，绘制下一条路线

private :

    Ui::MainWindow *ui;

    static const int MAX_VERTEX_NUM = 114;
    static const int INF = 9999;

    //MapWidget *mapWidget
    //QComboBox *reviseComboBox;
    //关于图和寻路算法的实现
    typedef struct {//边信息
        int dis;//权值
    }Arc;

    typedef struct {

        QVector<int> vex;//顶点类型
        Arc arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//存储边的矩阵
        double congestion[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //存储拥挤度
        int vexnum;//顶点数
        int arcnum;//边数
    }MGraph;

    class findShortestPath{
        public:

            MGraph Map;
            int prev[MAX_VERTEX_NUM];//最短路上各前驱结点
            double distance[MAX_VERTEX_NUM];//表示权值
            bool used[MAX_VERTEX_NUM];//已被使用过的图

            findShortestPath();
            ~findShortestPath();
            void createGraph();
            void findPath(int startPos, int flag);//求出从起点到各点的最短路径。可能要改为用终点
            QVector<int> getPath(int endPos);//到终点的最短路径
            void setCongestion();
    };


    findShortestPath *tour;

    int idLocation = 1;//全局变量，表示当前是整条路线的第几个点
    int traffic = 0;
    int leastTimeFlag =0;
    int startX=20, startY=50, endX=20, endY=50,midX=20, midY=50,tmpX=20,tmpY=50;

    QLabel * userLabel;
    QLabel *startLabel;
    QLabel *endLabel;
    QLabel *midLabel;

    QLabel *logicLabel, *trafficLabe;

    QComboBox *logicCombo, *trafficCombo;

    QComboBox *userComboBox;
    QComboBox *startComboBox;
    QComboBox *endComboBox;
    QComboBox *midComboBox;

    QAction *findPathAction,*clearAction, *multiFindAction, *ctrlAction, *leastTimeAct;
    QPropertyAnimation * ani;
    //QFrame * frame;
    QVector<int> nextPath, nextPath_mid;

    QPixmap somePlace;//需要特殊展示的地点，可有多个
    QString strPath; //读取文件的路径
    QLabel *label;


protected:  //鼠标事件
    void mouseDoubleClikEvent(QMouseEvent*event);
    //virtual void paintEvent(QPaintEvent* event)override;
    //virtual void mousePressEvent(QMouseEvent *event) override;


};
#endif // MAINWINDOW_H
