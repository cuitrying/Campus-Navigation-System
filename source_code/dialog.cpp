#include "mainwindow.h"

void MainWindow::printLog(const QString& s)//打印日志
{
    QFile file;
    file.setFileName("./log.txt");
    if(file.open(QIODevice::ReadWrite |QIODevice::Append)){
            QTextStream stream(&file);
            stream<<printTime(timeChange())<<"  "<<s<<"\n";
            file.close();
            //qDebug()<<"--------------------close--------------------"<<"\n";
    }
}

int MainWindow::timeChange()//时间映射转换
{
    QTime current_time =QTime::currentTime();
    int time_all;
    time_all =  current_time.hour()*60*60 + current_time.minute()*60 + current_time.second();
    int time_change;
    time_change = time_all % 7200;//相当于两小时
    return time_change;
}


QString MainWindow::printTime(int i)//输出时间
{
    QString time_return;
    time_return += QString::number(i/300) + ":" + QString::number((i%300)/5);
    return time_return;
}

void MainWindow::Delay_MSec(unsigned int msec)//用来延迟
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}
