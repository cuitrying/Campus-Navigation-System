#include "insidewidget.h"
#include "ui_insidewidget.h"

insideWidget::insideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::insideWidget)
{
    setWindowTitle("S4楼内地图");
    ui->setupUi(this);
}

insideWidget::~insideWidget()
{
    delete ui;
}

void insideWidget::on_pushButton_clicked()
{
    if(ui->stackedWidget->currentWidget() != ui->page){
        ui->stackedWidget->setCurrentWidget(ui->page);
    }
}

void insideWidget::on_pushButton_2_clicked()
{
    if(ui->stackedWidget->currentWidget() != ui->page_2){
        ui->stackedWidget->setCurrentWidget(ui->page_2);
    }
}
