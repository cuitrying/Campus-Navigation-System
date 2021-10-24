#include <QMessageBox>
#include <QPainter>
#include <QSequentialAnimationGroup>
#include "windows.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "insidewidget.h"
#include "ui_insidewidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    leastTimeFlag = 0;
    setWindowTitle("BUPT校园导览系统");
    ui->setupUi(this);
    createAction();
    initMainWindow();


    tour = new MainWindow::findShortestPath();
    tour->createGraph();
    tour->setCongestion();

    ani = new QPropertyAnimation(ui->frame,"geometry");//指定动画对象
    //frame = ui->frame;

    clear();
    connect(this,SIGNAL(aniSignal()),this,SLOT(paintAni()));//日志打印完成后绘制下一条路
    //connect(userComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeUser()));//切換用戶
}

//初始化ui界面
void MainWindow::initMainWindow()
{

    ui->toolBar->addAction(findPathAction);
    ui->toolBar->addSeparator();

    ui->toolBar->addAction(ctrlAction);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(clearAction);
    ui->toolBar->addSeparator();

    ui->toolBar->addAction(leastTimeAct);
    ui->toolBar->addSeparator();
/*
    userLabel = new QLabel;
    userLabel->setText("用户");
    userComboBox = new QComboBox;
    ui->toolBar->addWidget(userLabel);
    ui->toolBar->addWidget(userComboBox);

    userComboBox->addItem("用户1");
    userComboBox->addItem("用户2");
    userComboBox->addItem("用户3");
    */
//--------------------------------------------------------
    ui->toolBar->addSeparator();

    startLabel = new QLabel;
    startLabel->setText("起点:");
    startComboBox = new QComboBox;
    ui->toolBar->addWidget(startLabel);
    ui->toolBar->addWidget(startComboBox);

        startComboBox->addItem("(以下为地点列表)");
        startComboBox->addItem("雁北园北区西北角");
        startComboBox->addItem("雁北园北区东北角");
        startComboBox->addItem("沙河-医务室");
        startComboBox->addItem("综合办公楼东北角");
        startComboBox->addItem("沙河-运动场");
        startComboBox->addItem("雁北园北区西南角");
        startComboBox->addItem("沙河-雁北园北区");
        startComboBox->addItem("沙河-洗衣店");
        startComboBox->addItem( "沙河-教工食堂");
        startComboBox->addItem( "沙河-二维码广场");
        startComboBox->addItem( "沙河-综合办公楼");
        startComboBox->addItem("综合办公楼东南角");
        startComboBox->addItem( "沙河-东配楼");
        startComboBox->addItem( "沙河-雁北园南区");
        startComboBox->addItem( "沙河-小麦铺");
        startComboBox->addItem( "沙河-球场");
        startComboBox->addItem("雁北园南区西");
        startComboBox->addItem( "沙河-学生食堂");
        startComboBox->addItem( "沙河-西餐厅");
        startComboBox->addItem( "沙河-学生活动中心&邮局");
        startComboBox->addItem( "沙河-校西门");
        startComboBox->addItem( "沙河-菜鸟驿站");
        startComboBox->addItem("鸿雁路西");
        startComboBox->addItem( "沙河-商贸服务区");
        startComboBox->addItem("鸿雁路中西");
        startComboBox->addItem("鸿雁路中");
        startComboBox->addItem( "沙河-图书馆" );
        startComboBox->addItem( "沙河-教学实验综合楼&报告厅" );
        startComboBox->addItem("鸿雁路东");
        startComboBox->addItem( "沙河-雁南园S2" );
        startComboBox->addItem( "沙河-雁南园S3" );
        startComboBox->addItem("雁南园S3后侧");
        startComboBox->addItem( "沙河-雁南园S4" );
        startComboBox->addItem("雁南园S4后侧");
        startComboBox->addItem( "沙河-雁南园S5北" );//起点的名称
        startComboBox->addItem( "沙河-雁南园S6" );
        startComboBox->addItem("雁南园S5南");


        startComboBox->addItem("西土城-校北门");
        startComboBox->addItem("西土城-学十一公寓");
        startComboBox->addItem("西土城-经管楼");
        startComboBox->addItem("西土城-学六公寓");
        startComboBox->addItem("西土城-家属区");
        startComboBox->addItem("西土城-科研大楼");
        startComboBox->addItem("西土城-校东北门&青年教师公寓");
        startComboBox->addItem("西土城-留学生公寓");
        startComboBox->addItem("西土城-学九公寓");
        startComboBox->addItem("西土城-学十公寓");
        startComboBox->addItem("西土城-学生活动中心西门");
        startComboBox->addItem("西土城-青年公寓");
        startComboBox->addItem("西土城-综合食堂");
        startComboBox->addItem("学五公寓西北角");//14
        startComboBox->addItem("西土城-外卖窗口西");
        startComboBox->addItem("西土城-外卖窗口东");
        startComboBox->addItem("西土城-学苑超市");
        startComboBox->addItem("西土城-水房澡堂锅炉房");
        startComboBox->addItem("西土城-学五公寓");
        startComboBox->addItem("西土城-喷泉北");
        startComboBox->addItem("西土城-学八公寓");
        startComboBox->addItem("西土城-教工餐厅");
        startComboBox->addItem("喷泉东");//23
        startComboBox->addItem("西土城-小松林");
        startComboBox->addItem("西土城-学苑书屋");
        startComboBox->addItem("西土城-学十三公寓");
        startComboBox->addItem("西土城-学三公寓");
        startComboBox->addItem("喷泉南");//28
        startComboBox->addItem("西土城-学四公寓");
        startComboBox->addItem("学四东");//30
        startComboBox->addItem("西土城-球场");
        startComboBox->addItem("西土城-学生食堂");
        startComboBox->addItem("西土城-家属区&保卫处");
        startComboBox->addItem("西土城-图书馆");
        startComboBox->addItem("西土城-鸿雁楼");
        startComboBox->addItem("西土城-学一公寓");
        startComboBox->addItem("学一学二路口");//37
        startComboBox->addItem("西土城-学二公寓");
        startComboBox->addItem("西土城-时光广场路口");
        startComboBox->addItem("西土城-行政办公楼");
        startComboBox->addItem("西土城-篮球场");
        startComboBox->addItem("西土城-网球场排球场");
        startComboBox->addItem("西土城-体育馆");
        startComboBox->addItem("西土城-游泳馆&学29公寓");
        startComboBox->addItem("西土城-校东门");
        startComboBox->addItem("西土城-财务处&后勤楼");
        startComboBox->addItem("西土城-移动营业厅");
        startComboBox->addItem("西土城-教四楼");
        startComboBox->addItem("主干道中");//49
        startComboBox->addItem("西土城-教一楼");
        startComboBox->addItem("教一楼东南角");//51
        startComboBox->addItem("西土城-科学会堂");
        startComboBox->addItem("西土城-全民健身");
        startComboBox->addItem("西土城-校西门&主席像");
        startComboBox->addItem("西土城-主楼&音乐喷泉");
        startComboBox->addItem("西土城-体育场");
        startComboBox->addItem("西土城-停车坪");
        startComboBox->addItem("西土城-教三楼");
        startComboBox->addItem("主干道南");//59
        startComboBox->addItem("西土城-教二楼");
        startComboBox->addItem("教二楼东北角");//61
        startComboBox->addItem("科学会堂西南角");//62
        startComboBox->addItem("科学会堂东南角");//63
        startComboBox->addItem("西土城-中门邮局");
        startComboBox->addItem("教二楼东南角");//65
        startComboBox->addItem("西土城-可信网络通信协同创新中心");
        startComboBox->addItem("西土城-时光咖啡店");
        startComboBox->addItem("西土城-校医院");
        startComboBox->addItem("西土城-中门");
        startComboBox->addItem("西土城-南区超市");
        startComboBox->addItem("西土城-南门");
        startComboBox->addItem("学五公寓西南角");//72
        startComboBox->addItem("学八公寓东南角");//73
        startComboBox->addItem("西土城-校车车库");
        startComboBox->addItem("西土城-体育场西南角");

        startComboBox->addItem("转折点1");//转折点1
        startComboBox->addItem("转折点2");//转折点2

        QListView *view = qobject_cast<QListView *>(startComboBox->view());
            Q_ASSERT(view!=nullptr);

            view->setRowHidden(1, true);
            view->setRowHidden(2, true);
            view->setRowHidden(4, true);
            view->setRowHidden(6, true);
            view->setRowHidden(12, true);
            view->setRowHidden(17, true);
            view->setRowHidden(23, true);
            view->setRowHidden(25, true);
            view->setRowHidden(26, true);
            view->setRowHidden(29, true);
            view->setRowHidden(32, true);
            view->setRowHidden(34, true);
            view->setRowHidden(37, true);

            view->setRowHidden(37+14, true);
            view->setRowHidden(37+23, true);
            view->setRowHidden(37+28, true);
            view->setRowHidden(37+30, true);
            view->setRowHidden(37+37, true);
            view->setRowHidden(37+49, true);
            view->setRowHidden(37+51, true);
            view->setRowHidden(37+59, true);
            view->setRowHidden(37+61, true);
            view->setRowHidden(37+62, true);
            view->setRowHidden(37+63, true);
            view->setRowHidden(37+65, true);
            view->setRowHidden(37+72, true);
            view->setRowHidden(37+73, true);

            view->setRowHidden(37+76, true);
            view->setRowHidden(37+77, true);


//--------------------------------------------------------
    ui->toolBar->addSeparator();

    midLabel = new QLabel;
    midLabel->setText("必经点:");
    midComboBox = new QComboBox;
    ui->toolBar->addWidget(midLabel);
    ui->toolBar->addWidget(midComboBox);

    midComboBox->addItem( "无" );
        midComboBox->addItem("");
        midComboBox->addItem("");
        midComboBox->addItem("沙河-医务室");
        midComboBox->addItem("");
        midComboBox->addItem("沙河-运动场");
        midComboBox->addItem("");
        midComboBox->addItem("沙河-雁北园北区");
        midComboBox->addItem("沙河-洗衣店");
        midComboBox->addItem( "沙河-教工食堂");
        midComboBox->addItem( "沙河-二维码广场");
        midComboBox->addItem( "沙河-综合办公楼");
        midComboBox->addItem("");
        midComboBox->addItem( "沙河-东配楼");
        midComboBox->addItem( "沙河-雁北园南区");
        midComboBox->addItem( "沙河-小麦铺");
        midComboBox->addItem( "沙河-球场");
        midComboBox->addItem("");
        midComboBox->addItem( "沙河-学生食堂");
        midComboBox->addItem( "沙河-西餐厅");
        midComboBox->addItem( "沙河-学生活动中心&邮局");
        midComboBox->addItem( "沙河-校西门");
        midComboBox->addItem( "沙河-菜鸟驿站");
        midComboBox->addItem("");
        midComboBox->addItem( "沙河-商贸服务区");
        midComboBox->addItem("");
        midComboBox->addItem("");
        midComboBox->addItem( "沙河-图书馆" );
        midComboBox->addItem( "沙河-教学实验综合楼&报告厅" );
        midComboBox->addItem("");
        midComboBox->addItem( "沙河-雁南园S2" );
        midComboBox->addItem( "沙河-雁南园S3" );
        midComboBox->addItem("");
        midComboBox->addItem( "沙河-雁南园S4" );
        midComboBox->addItem("");
        midComboBox->addItem( "沙河-雁南园S5北" );//起点的名称
        midComboBox->addItem( "沙河-雁南园S6" );
        midComboBox->addItem("");


        midComboBox->addItem("西土城-校北门");
        midComboBox->addItem("西土城-学十一公寓");
        midComboBox->addItem("西土城-经管楼");
        midComboBox->addItem("西土城-学六公寓");
        midComboBox->addItem("西土城-家属区");
        midComboBox->addItem("西土城-科研大楼");
        midComboBox->addItem("西土城-校东北门&青年教师公寓");
        midComboBox->addItem("西土城-留学生公寓");
        midComboBox->addItem("西土城-学九公寓");
        midComboBox->addItem("西土城-学十公寓");
        midComboBox->addItem("西土城-学生活动中心西门");
        midComboBox->addItem("西土城-青年公寓");
        midComboBox->addItem("西土城-综合食堂");
        midComboBox->addItem("");//14
        midComboBox->addItem("西土城-外卖窗口西");
        midComboBox->addItem("西土城-外卖窗口东");
        midComboBox->addItem("西土城-学苑超市");
        midComboBox->addItem("西土城-水房澡堂锅炉房");
        midComboBox->addItem("西土城-学五公寓");
        midComboBox->addItem("西土城-喷泉北");
        midComboBox->addItem("西土城-学八公寓");
        midComboBox->addItem("西土城-教工餐厅");
        midComboBox->addItem("");//23
        midComboBox->addItem("西土城-小松林");
        midComboBox->addItem("西土城-学苑书屋");
        midComboBox->addItem("西土城-学十三公寓");
        midComboBox->addItem("西土城-学三公寓");
        midComboBox->addItem("");//28
        midComboBox->addItem("西土城-学四公寓");
        midComboBox->addItem("");//30
        midComboBox->addItem("西土城-球场");
        midComboBox->addItem("西土城-学生食堂");
        midComboBox->addItem("西土城-家属区&保卫处");
        midComboBox->addItem("西土城-图书馆");
        midComboBox->addItem("西土城-鸿雁楼");
        midComboBox->addItem("西土城-学一公寓");
        midComboBox->addItem("");//37
        midComboBox->addItem("西土城-学二公寓");
        midComboBox->addItem("西土城-时光广场路口");
        midComboBox->addItem("西土城-行政办公楼");
        midComboBox->addItem("西土城-篮球场");
        midComboBox->addItem("西土城-网球场排球场");
        midComboBox->addItem("西土城-体育馆");
        midComboBox->addItem("西土城-游泳馆&学29公寓");
        midComboBox->addItem("西土城-校东门");
        midComboBox->addItem("西土城-财务处&后勤楼");
        midComboBox->addItem("西土城-移动营业厅");
        midComboBox->addItem("西土城-教四楼");
        midComboBox->addItem("");//49
        midComboBox->addItem("西土城-教一楼");
        midComboBox->addItem("");//51
        midComboBox->addItem("西土城-科学会堂");
        midComboBox->addItem("西土城-全民健身");
        midComboBox->addItem("西土城-校西门&主席像");
        midComboBox->addItem("西土城-主楼&音乐喷泉");
        midComboBox->addItem("西土城-体育场");
        midComboBox->addItem("西土城-停车坪");
        midComboBox->addItem("西土城-教三楼");
        midComboBox->addItem("");//59
        midComboBox->addItem("西土城-教二楼");
        midComboBox->addItem("");//61
        midComboBox->addItem("");//62
        midComboBox->addItem("");//63
        midComboBox->addItem("西土城-中门邮局");
        midComboBox->addItem("");//65
        midComboBox->addItem("西土城-可信网络通信协同创新中心");
        midComboBox->addItem("西土城-时光咖啡店");
        midComboBox->addItem("西土城-校医院");
        midComboBox->addItem("西土城-中门");
        midComboBox->addItem("西土城-南区超市");
        midComboBox->addItem("西土城-南门");
        midComboBox->addItem("");//72
        midComboBox->addItem("");//73
        midComboBox->addItem("西土城-校车车库");
        midComboBox->addItem("西土城-体育场西南角");

        midComboBox->addItem("");//转折点1
        midComboBox->addItem("");//转折点2

        QListView *midview = qobject_cast<QListView *>(midComboBox->view());
        Q_ASSERT(midview!=nullptr);

        midview->setRowHidden(1, true);
        midview->setRowHidden(2, true);
        midview->setRowHidden(4, true);
        midview->setRowHidden(6, true);
        midview->setRowHidden(12, true);
        midview->setRowHidden(17, true);
        midview->setRowHidden(23, true);
        midview->setRowHidden(25, true);
        midview->setRowHidden(26, true);
        midview->setRowHidden(29, true);
        midview->setRowHidden(32, true);
        midview->setRowHidden(34, true);
        midview->setRowHidden(37, true);

        midview->setRowHidden(37+14, true);
        midview->setRowHidden(37+23, true);
        midview->setRowHidden(37+28, true);
        midview->setRowHidden(37+30, true);
        midview->setRowHidden(37+37, true);
        midview->setRowHidden(37+49, true);
        midview->setRowHidden(37+51, true);
        midview->setRowHidden(37+59, true);
        midview->setRowHidden(37+61, true);
        midview->setRowHidden(37+62, true);
        midview->setRowHidden(37+63, true);
        midview->setRowHidden(37+65, true);
        midview->setRowHidden(37+72, true);
        midview->setRowHidden(37+73, true);

        midview->setRowHidden(37+76, true);
        midview->setRowHidden(37+77, true);
//--------------------------------------------------------
    ui->toolBar->addSeparator();

    endLabel = new QLabel;
    endLabel->setText("终点:");
    endComboBox = new QComboBox;
    ui->toolBar->addWidget(endLabel);
    ui->toolBar->addWidget(endComboBox);

    endComboBox->addItem("(以下为地点列表)");
        endComboBox->addItem("");
        endComboBox->addItem("");
        endComboBox->addItem("沙河-医务室");
        endComboBox->addItem("");
        endComboBox->addItem("沙河-运动场");
        endComboBox->addItem("");
        endComboBox->addItem("沙河-雁北园北区");
        endComboBox->addItem("沙河-洗衣店");
        endComboBox->addItem( "沙河-教工食堂");
        endComboBox->addItem( "沙河-二维码广场");
        endComboBox->addItem( "沙河-综合办公楼");
        endComboBox->addItem("");
        endComboBox->addItem( "沙河-东配楼");
        endComboBox->addItem( "沙河-雁北园南区");
        endComboBox->addItem( "沙河-小麦铺");
        endComboBox->addItem( "沙河-球场");
        endComboBox->addItem("");
        endComboBox->addItem( "沙河-学生食堂");
        endComboBox->addItem( "沙河-西餐厅");
        endComboBox->addItem( "沙河-学生活动中心&邮局");
        endComboBox->addItem( "沙河-校西门");
        endComboBox->addItem( "沙河-菜鸟驿站");
        endComboBox->addItem("");
        endComboBox->addItem( "沙河-商贸服务区");
        endComboBox->addItem("");
        endComboBox->addItem("");
        endComboBox->addItem( "沙河-图书馆" );
        endComboBox->addItem( "沙河-教学实验综合楼&报告厅" );
        endComboBox->addItem("");
        endComboBox->addItem( "沙河-雁南园S2" );
        endComboBox->addItem( "沙河-雁南园S3" );
        endComboBox->addItem("");
        endComboBox->addItem( "沙河-雁南园S4" );
        endComboBox->addItem("");
        endComboBox->addItem( "沙河-雁南园S5北" );//起点的名称
        endComboBox->addItem( "沙河-雁南园S6" );
        endComboBox->addItem("");


        endComboBox->addItem("西土城-校北门");
        endComboBox->addItem("西土城-学十一公寓");
        endComboBox->addItem("西土城-经管楼");
        endComboBox->addItem("西土城-学六公寓");
        endComboBox->addItem("西土城-家属区");
        endComboBox->addItem("西土城-科研大楼");
        endComboBox->addItem("西土城-校东北门&青年教师公寓");
        endComboBox->addItem("西土城-留学生公寓");
        endComboBox->addItem("西土城-学九公寓");
        endComboBox->addItem("西土城-学十公寓");
        endComboBox->addItem("西土城-学生活动中心西门");
        endComboBox->addItem("西土城-青年公寓");
        endComboBox->addItem("西土城-综合食堂");
        endComboBox->addItem("");//14
        endComboBox->addItem("西土城-外卖窗口西");
        endComboBox->addItem("西土城-外卖窗口东");
        endComboBox->addItem("西土城-学苑超市");
        endComboBox->addItem("西土城-水房澡堂锅炉房");
        endComboBox->addItem("西土城-学五公寓");
        endComboBox->addItem("西土城-喷泉北");
        endComboBox->addItem("西土城-学八公寓");
        endComboBox->addItem("西土城-教工餐厅");
        endComboBox->addItem("");//23
        endComboBox->addItem("西土城-小松林");
        endComboBox->addItem("西土城-学苑书屋");
        endComboBox->addItem("西土城-学十三公寓");
        endComboBox->addItem("西土城-学三公寓");
        endComboBox->addItem("");//28
        endComboBox->addItem("西土城-学四公寓");
        endComboBox->addItem("");//30
        endComboBox->addItem("西土城-球场");
        endComboBox->addItem("西土城-学生食堂");
        endComboBox->addItem("西土城-家属区&保卫处");
        endComboBox->addItem("西土城-图书馆");
        endComboBox->addItem("西土城-鸿雁楼");
        endComboBox->addItem("西土城-学一公寓");
        endComboBox->addItem("");//37
        endComboBox->addItem("西土城-学二公寓");
        endComboBox->addItem("西土城-时光广场路口");
        endComboBox->addItem("西土城-行政办公楼");
        endComboBox->addItem("西土城-篮球场");
        endComboBox->addItem("西土城-网球场排球场");
        endComboBox->addItem("西土城-体育馆");
        endComboBox->addItem("西土城-游泳馆&学29公寓");
        endComboBox->addItem("西土城-校东门");
        endComboBox->addItem("西土城-财务处&后勤楼");
        endComboBox->addItem("西土城-移动营业厅");
        endComboBox->addItem("西土城-教四楼");
        endComboBox->addItem("");//49
        endComboBox->addItem("西土城-教一楼");
        endComboBox->addItem("");//51
        endComboBox->addItem("西土城-科学会堂");
        endComboBox->addItem("西土城-全民健身");
        endComboBox->addItem("西土城-校西门&主席像");
        endComboBox->addItem("西土城-主楼&音乐喷泉");
        endComboBox->addItem("西土城-体育场");
        endComboBox->addItem("西土城-停车坪");
        endComboBox->addItem("西土城-教三楼");
        endComboBox->addItem("");//59
        endComboBox->addItem("西土城-教二楼");
        endComboBox->addItem("");//61
        endComboBox->addItem("");//62
        endComboBox->addItem("");//63
        endComboBox->addItem("西土城-中门邮局");
        endComboBox->addItem("");//65
        endComboBox->addItem("西土城-可信网络通信协同创新中心");
        endComboBox->addItem("西土城-时光咖啡店");
        endComboBox->addItem("西土城-校医院");
        endComboBox->addItem("西土城-中门");
        endComboBox->addItem("西土城-南区超市");
        endComboBox->addItem("西土城-南门");
        endComboBox->addItem("");//72
        endComboBox->addItem("");//73
        endComboBox->addItem("西土城-校车车库");
        endComboBox->addItem("西土城-体育场西南角");

        endComboBox->addItem("");//转折点1
        endComboBox->addItem("");//转折点2

        QListView *endview = qobject_cast<QListView *>(endComboBox->view());
        Q_ASSERT(endview!=nullptr);

        endview->setRowHidden(1, true);
        endview->setRowHidden(2, true);
        endview->setRowHidden(4, true);
        endview->setRowHidden(6, true);
        endview->setRowHidden(12, true);
        endview->setRowHidden(17, true);
        endview->setRowHidden(23, true);
        endview->setRowHidden(25, true);
        endview->setRowHidden(26, true);
        endview->setRowHidden(29, true);
        endview->setRowHidden(32, true);
        endview->setRowHidden(34, true);
        endview->setRowHidden(37, true);

        endview->setRowHidden(37+14, true);
        endview->setRowHidden(37+23, true);
        endview->setRowHidden(37+28, true);
        endview->setRowHidden(37+30, true);
        endview->setRowHidden(37+37, true);
        endview->setRowHidden(37+49, true);
        endview->setRowHidden(37+51, true);
        endview->setRowHidden(37+59, true);
        endview->setRowHidden(37+61, true);
        endview->setRowHidden(37+62, true);
        endview->setRowHidden(37+63, true);
        endview->setRowHidden(37+65, true);
        endview->setRowHidden(37+72, true);
        endview->setRowHidden(37+73, true);

        endview->setRowHidden(37+76, true);
        endview->setRowHidden(37+77, true);
//--------------------------------------------------------
        ui->toolBar->addSeparator();

        logicLabel = new QLabel;
        logicLabel->setText("逻辑功能:");
        logicCombo = new QComboBox;
        ui->toolBar->addWidget(logicLabel);
        ui->toolBar->addWidget(logicCombo);

        logicCombo->addItem("请选需要的功能(沙河)");    //加入拥塞系数，
        logicCombo->addItem("运动");//1   操场——球场
        logicCombo->addItem("吃饭");//2   两个食堂
        logicCombo->addItem("购物");//3   小卖铺和超市

//--------------------------------------------------------
        ui->toolBar->addSeparator();

        trafficLabe = new QLabel;
        trafficLabe->setText("交通方式:");
        trafficCombo = new QComboBox;
        ui->toolBar->addWidget(trafficLabe);
        ui->toolBar->addWidget(trafficCombo);

        trafficCombo->addItem("步行");    //默认交通方式为步行 0
        trafficCombo->addItem("骑车");    //1
}

void MainWindow::createAction(){
    findPathAction = new QAction(QIcon(":/image/Search.png"),tr("搜索路径"), this);
    findPathAction->setShortcut (tr("Ctrl+F"));
    findPathAction->setStatusTip (tr("搜索路径"));
    connect (findPathAction, SIGNAL(triggered(bool)), this, SLOT(navigation()));

    clearAction = new QAction(QIcon(":/image/Clear.png"), tr("清理路径"), this);
    clearAction->setShortcut (tr("Ctrl+W"));
    clearAction->setStatusTip (tr("清理路径"));
    connect (clearAction, SIGNAL(triggered(bool)), this, SLOT(clear()));

    multiFindAction = new QAction (QIcon("Multi.png"), tr("中间最短"), this);
    multiFindAction->setShortcut(tr("Ctrl+G"));
    multiFindAction->setStatusTip(tr("中间最短路径"));
    connect(multiFindAction, SIGNAL(triggered(bool)), this, SLOT(multiFind()));

    ctrlAction = new QAction(QIcon(":/image/Ctrl.png"), tr("控制"),this);
    ctrlAction->setShortcut(tr("Ctrl+Q"));
    connect(ctrlAction, SIGNAL(triggered(bool)), this, SLOT(control()));

    leastTimeAct = new QAction(QIcon(":/image/timeMode.jpg"), tr("最短时间"), this);
    leastTimeAct->setShortcut(tr("Ctrl+E"));
    leastTimeAct->setStatusTip(tr("采用最短时间策略"));
    connect(leastTimeAct, SIGNAL(triggered(bool)), this, SLOT(leastTimeMode()));
}

void MainWindow::clear(){

    //回到启动界面的位置
    ani = new QPropertyAnimation(ui->frame,"geometry");
    ani->setDuration(100);
    ani->setStartValue(QRect(1, -5, 40, 50));
    ani->setEndValue(QRect(1, -5,40, 50));
    ani->start();
    idLocation = 1;
    printLog("clear");
    screenLog("clear");
    //leastTimeFlag =0;
}

void MainWindow::paintPath(){

    QMessageBox::information(this, "oo", "开始实时导航", QMessageBox::Ok);

    if(ani->state() == QPropertyAnimation::Paused && idLocation!=1)//这样就可以中间暂停后再次选择终点
        startComboBox->setCurrentIndex(nextPath[idLocation-2]+1);

    tour->findPath(startComboBox->currentIndex()-1, leastTimeFlag);  //根据起点寻路
    nextPath = tour->getPath(endComboBox->currentIndex()-1);      //根据终点选择绘制路线

    qDebug()<<"起点是：\n"<<startComboBox->currentText()<<"\n"<<startComboBox->currentIndex()<<"\n"<<"终点是：\n"<<endComboBox->currentText()<<"\n"<<endComboBox->currentIndex()<<"\n";

    //调用出错了
    clear();//清除界面以准备绘制路线

    for(int i = 1; i< nextPath.size(); i++ ){
        qDebug() << nextPath[i]+1 <<"_\n";
    }

    //处理坐标
    setStartStation();
    setEndStation();
    QPoint tmp1(startX, startY),tmp2(endX, endY);

    //动画
    ani->setDuration(30);
    ani->setStartValue(QRect(startX-13, startY-50, 30, 40));
    ani->setEndValue(QRect(endX-13, endY-50,30, 40));
    qDebug()<<"start:"<<startX<<" "<<startY<<"_\n";
    qDebug()<<"end:"<<endX<<" "<<endY<<"_\n";


    QString strtmp,temp;
    qDebug()<<"size:"<<nextPath.size()<<"_\n";

    qDebug()<<"start"<<"_\n";
    printLog("---------------------------------------------");
    screenLog("------------------------");

    //先打印起点
    QString str_temp =startComboBox->itemText(nextPath[0]+1);
    temp = QString::number(nextPath[0]+1);//获取重点的标号
    strtmp = "用户已到：" + temp + "->" + str_temp;
    printLog(strtmp);
    screenLog(strtmp);

    //需要一个start来触发finished()信号
    ani->setStartValue(QRect(50, 50, 30, 40));
    ani->setEndValue(QRect(50, 50,30, 40));
    ani->start();
    connect(ani,SIGNAL(finished()),this,SLOT(paintLog()));

}

void MainWindow::multiFind(){

    QMessageBox::information(this, "oo", "开始实时导航", QMessageBox::Ok);

    if(ani->state() == QPropertyAnimation::Paused && idLocation!=1)//这样就可以中间暂停后再次选择终点
        startComboBox->setCurrentIndex(nextPath[idLocation-2]+1);

    tour->findPath(startComboBox->currentIndex()-1, leastTimeFlag);  //根据起点寻路
    nextPath = tour->getPath(midComboBox->currentIndex()-1);
    tour->findPath(midComboBox->currentIndex()-1, leastTimeFlag);
    nextPath_mid = tour->getPath(endComboBox->currentIndex()-1);      //根据终点选择绘制路线

    for(int i = 1; i<nextPath_mid.size(); i++)//跳过第二段的第一个点，因为这个点也是第一段的最后一个
    {
        nextPath.push_back(nextPath_mid[i]);
    }
    //已经将两段路合并为一段路
    qDebug()<<"起点是：\n"<<startComboBox->currentText()<<"\n"<<startComboBox->currentIndex()<<"\n"<<"中间点是：\n"
           <<midComboBox->currentText()<<"\n"<<midComboBox->currentIndex()<<"\n"<<"终点是：\n"
          <<endComboBox->currentText()<<"\n"<<endComboBox->currentIndex()<<"\n";


    //调用出错了
    clear();//清除界面以准备绘制路线

    for(int i = 1; i< nextPath.size(); i++ ){
        qDebug() << nextPath[i]+1 <<"_\n";
    }

    //处理坐标
    setStartStation();
    setMidStation();
    setEndStation();

    ani->setDuration(30);
    ani->setStartValue(QRect(startX-13, startY-50, 30, 40));
    ani->setEndValue(QRect(endX-13, endY-50,30, 40));
    qDebug()<<"start:"<<startX<<" "<<startY<<"_\n";
    qDebug()<<"mid:"<<midX<<" "<<midY<<"_\n";
    qDebug()<<"end:"<<endX<<" "<<endY<<"_\n";


    QString strtmp,temp;

    //先打印开始的地点
    qDebug()<<"start"<<"_\n";
    printLog("---------------------------------------------");
    screenLog("------------------------");
    QString str_temp =startComboBox->itemText(nextPath[0]+1);
    temp = QString::number(nextPath[0]+1);//获取重点的标号
    strtmp = "用户已到：" + temp + "->" + str_temp;
    printLog(strtmp);
    screenLog(strtmp);

    ani->setStartValue(QRect(50, 50, 30, 40));
    ani->setEndValue(QRect(50, 50,30, 40));
    ani->start();
    connect(ani,SIGNAL(finished()),this,SLOT(paintLog()));
}

void MainWindow::aroundBuilding(int num)//找出周围的点，也就是建筑
{
    if((nextPath[num-1]+1)!=0){
        ui->around->document()->setMaximumBlockCount(20);
        ui->around->clear();//先清空界面
        QString str_temp = startComboBox->itemText(nextPath[num-1]+1);//目前到达的点
        ui->around->append("目前位置："+str_temp + "\n");
        int now = nextPath[num-1];
        double dist;
        //下面我们要寻找这个点周围的点，也就是可直达的点
        for(int i = 0; i < (tour->Map.vexnum)-1; i++)
        {
            if(tour->Map.arc[now][i].dis<9999)//如果距离小于9999，则为可达
            {
                str_temp = startComboBox->itemText(i+1);
                dist = tour->Map.arc[now][i].dis;
                ui->around->append("可达：" + str_temp );
                ui->around->append(" distance: " + QString::number(dist));
            }
        }
    }
}

void MainWindow::congestionControl(){

    if(startComboBox->currentIndex()==0)
        startComboBox->setCurrentIndex(21); //实现的是沙河功能，默认从西门开始
    else if(idLocation!=1)//如果已经开始寻路
        startComboBox->setCurrentIndex(nextPath[idLocation-2]+1);
    int time  = (timeChange()/10)%2;    //每十秒变化一次
    if(time == 0){  //选择第一（0）个选项
        if(logicCombo->currentText() == "吃饭"){
            if(startComboBox->currentIndex() < 38)
            {
                endComboBox->setCurrentIndex(18);
                QMessageBox::information(this, "吃饭建议", "根据当前时间，推荐地点为沙河-学生食堂", QMessageBox::Ok);
            }
            else
            {
                endComboBox->setCurrentIndex(50);
                QMessageBox::information(this, "吃饭建议", "根据当前时间，推荐地点为西土城-综合食堂", QMessageBox::Ok);
            }

        }
        if(logicCombo->currentText() == "运动"){
            if(startComboBox->currentIndex() < 38)
            {
                endComboBox->setCurrentIndex(5);
                QMessageBox::information(this, "运动建议", "根据当前时间，推荐地点为沙河-运动场", QMessageBox::Ok);
            }
            else
            {
                endComboBox->setCurrentIndex(93);
                QMessageBox::information(this, "运动建议", "根据当前时间，推荐地点为本部-体育场", QMessageBox::Ok);
            }

        }
        if(logicCombo->currentText() == "购物"){
            if(startComboBox->currentIndex() < 38)
            {
                endComboBox->setCurrentIndex(15);
                QMessageBox::information(this, "购物建议", "根据当前时间，推荐地点为沙河-小麦铺", QMessageBox::Ok);
            }
            else
            {
                endComboBox->setCurrentIndex(54);
                QMessageBox::information(this, "购物建议", "根据当前时间，推荐地点为本部-学苑超市", QMessageBox::Ok);
            }

        }
    }
    else if(time == 1){     //选择第二个选项
        if(logicCombo->currentText() == "吃饭"){
            if(startComboBox->currentIndex() < 38)
            {
                endComboBox->setCurrentIndex(9);
                QMessageBox::information(this, "吃饭建议", "根据当前时间，推荐地点为沙河-教工食堂", QMessageBox::Ok);
            }
            else
            {
                endComboBox->setCurrentIndex(69);
                QMessageBox::information(this, "吃饭建议", "根据当前时间，推荐地点为西土城-学生食堂", QMessageBox::Ok);
            }

        }
        if(logicCombo->currentText() == "运动"){
            if(startComboBox->currentIndex() < 38)
            {
                endComboBox->setCurrentIndex(16);
                QMessageBox::information(this, "运动建议", "根据当前时间，推荐地点为沙河-球场", QMessageBox::Ok);
            }
            else
            {
                endComboBox->setCurrentIndex(68);
                QMessageBox::information(this, "运动建议", "根据当前时间，推荐地点为本部-球场", QMessageBox::Ok);
            }

        }
        if(logicCombo->currentText() == "购物"){
            if(startComboBox->currentIndex() < 38)
            {
                endComboBox->setCurrentIndex(24);
                QMessageBox::information(this, "购物建议", "根据当前时间，推荐地点为沙河-商贸服务区", QMessageBox::Ok);
            }
            else
            {
                endComboBox->setCurrentIndex(54);
                QMessageBox::information(this, "购物建议", "根据当前时间，推荐地点为本部-学苑超市", QMessageBox::Ok);
            }

        }
    }

}

void MainWindow::leastTimeMode(){
    if(leastTimeFlag == 0)
    {
        printLog("least time");
        screenLog("least time");
        leastTimeFlag = 1;
    }
    else
    {
        printLog("least path");
        screenLog("least path");
        leastTimeFlag = 0;
    }
    //leastTimeFlag = 1;
}


void MainWindow::paintLog()
{
    if(idLocation!=1)
    {
            QString strtmp,temp, speed;
            QString str_temp =startComboBox->itemText(nextPath[idLocation-1]+1);//获取当前的地点名称
            temp = QString::number(nextPath[idLocation-1]+1);

            if(traffic == 1){
                speed = "-骑车";
            }
            else{
                speed = "";
            }

            strtmp = "用户已到：" + temp + "->" + str_temp + speed;
            printLog(strtmp);
            strtmp = printTime(timeChange()) + "  " + strtmp;
            screenLog(strtmp);

            //6.6 沙河西门、西土城东门处,向另一个校区移动时，需要考虑有无车辆
            if(idLocation!= nextPath.size()){
                if((nextPath[idLocation-1] == 81 && nextPath[idLocation] == 113)|| (nextPath[idLocation-1] == 20 && nextPath[idLocation] == 112)){
                 if((timeChange()/10)%2 == 0 ){   //默认第偶数个十秒有车，奇数个十秒无车；每十秒来车;
                     strtmp = "目前有班车,已发车";
                     printLog(strtmp);
                     screenLog(strtmp);
                     _sleep(2000);
                 }
                 else{   //需要等待一段时间
                     strtmp = "目前无班车,等待发车";
                     printLog(strtmp);
                     screenLog(strtmp);
                     for(int i = 10; i>0; i--){
                         strtmp = QString::number(i);
                         printLog(strtmp);
                         screenLog(strtmp);
                         _sleep(800);
                     }
                 }
                }
            }
    }
    aroundBuilding(idLocation);//打印周围可达
    emit aniSignal();//触发信号

    //ifS4();
}

void MainWindow::paintAni()//绘制一段动画
{
    if(idLocation<nextPath.size())
    {
        double unit_delay;
        int speedFlag = 1;
        //根据交通工具控制动画时间
        if((nextPath[idLocation-1] == 81 && nextPath[idLocation] == 113)||
                (nextPath[idLocation-1] == 20 && nextPath[idLocation] == 112) ||
                (nextPath[idLocation-1] == 113 && nextPath[idLocation] == 112) ||
                (nextPath[idLocation-1] == 112 && nextPath[idLocation] == 113)){
            speedFlag = 0;
        }
        else if(trafficCombo->currentIndex() == 0){  //走路速度就是默认
            speedFlag = 0;
        }
        unit_delay=30.0 - trafficCombo->currentIndex()*18*speedFlag;   //自行车快了一半多
        traffic = speedFlag;
        double delay = tour->Map.arc[nextPath[idLocation-1]][nextPath[idLocation]].dis*unit_delay;//此段动画时间
        ani->setDuration(delay);
        setNextPos(nextPath[idLocation-1]+1);//获取这段路的开始节点
        ani->setStartValue(QRect(tmpX-13, tmpY-50, 30, 40));
        setNextPos(nextPath[idLocation]+1);//获取这段路的目标节点
        ani->setEndValue(QRect(tmpX-13, tmpY-50, 30, 40));

        idLocation++;
        ani->start();
        //connect(ani,SIGNAL(finished()),this,SLOT(realPrint()));

    }
    else
        ifS4();
}

void MainWindow::screenLog(const QString &s)
{
    ui->log->document()->setMaximumBlockCount(20);
    ui->log->append(s);
}

void MainWindow::ifS4(){

    insideWidget * S4 = new insideWidget;

    if(idLocation == nextPath.size() && endComboBox->currentText() == "沙河-雁南园S4"){
        if(QMessageBox::Yes == QMessageBox::QMessageBox::information(NULL, "是否进入雁南S4", "进入选yes，不进点否",
                                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)){
            S4->show();
            screenLog("进入雁南S4");
            printLog("进入雁南S4");
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

