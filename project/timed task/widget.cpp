#include "widget.h"
#include "ui_widget.h"
#include<QPixmap>
#include<QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
  currentIndex(1)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Widget::nextpix);
    QString imgPath = QString(":/images/p%1.png").arg(currentIndex);
    QPixmap pix(imgPath);
        ui->picture->setPixmap(pix.scaled(ui->picture->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::nextpix()
{

currentIndex++;

if (currentIndex > 11) {

currentIndex = 1;
    }
QString imgPath = QString(":/images/p%1.png").arg(currentIndex);
QPixmap pix(imgPath);
    ui->picture->setPixmap(pix.scaled(ui->picture->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}



void Widget::on_start_clicked()
{
    timer->start(3000);
}

void Widget::on_stop_clicked()
{
    timer->stop();
}
