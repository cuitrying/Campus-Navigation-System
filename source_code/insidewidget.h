#ifndef INSIDEWIDGET_H
#define INSIDEWIDGET_H

#include <QWidget>

namespace Ui {
class insideWidget;
}

class insideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit insideWidget(QWidget *parent = nullptr);
    ~insideWidget();

private:
    Ui::insideWidget *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // INSIDEWIDGET_H
