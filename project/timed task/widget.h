#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
void nextpix();

void on_start_clicked();

void on_stop_clicked();

private:
    Ui::Widget *ui;
    int currentIndex;
    QTimer *timer;
};

#endif // WIDGET_H
