#include "mainwindow.h"

/*
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //ui->plainTextEdit->insertPlainText(" "+QString::number(event->x())+" "+QString::number(event->y())+'\n');
    QString tmp = QString::number(event->x())+","+ QString::number(event->y());
    QMessageBox::information(this, "pos",tmp, QMessageBox::Ok);
}
*/

void MainWindow::navigation(){
    if(logicCombo->currentIndex()!=0){
        congestionControl();
    }

    if(midComboBox->currentIndex() == 0){
        paintPath();
    }
    else{
        multiFind();
    }
}

void MainWindow::control(){

    //需要更新动画的状态，可能需要start
        if(ani->state() == QPropertyAnimation::Paused){
            ani->resume();
            screenLog("resume");
            printLog("resume");
        }
        else if(ani->state() == QPropertyAnimation::Running){
            ani->pause();
            screenLog("pause");
            printLog("pause");
        }
}

//该文件无法访问ui指针
