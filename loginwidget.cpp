#include "loginwidget.h"
#include <QPainter>
#include <QPixmap>
#include <QRect>
Loginwidget::Loginwidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
 //   setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoBackground);
    QDesktopWidget *d=QApplication::desktop();
    QRect sc=d->screenGeometry();
    setFixedSize(sc.width(),sc.height());
}

Loginwidget::~Loginwidget()
{

}
void Loginwidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(0, 0, this->width(), this->height()), QPixmap(":/qss/loginback"));
}
