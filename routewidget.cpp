#include "routewidget.h"

RouteWidget::RouteWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
}
void RouteWidget::setBackImg(int w ,int h)
{
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":/qss/infol").scaled(QSize(w,h),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);
}

RouteWidget::~RouteWidget()
{
}
void RouteWidget::paintEvent(QPaintEvent*)
{
   /*QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(0, 2, this->width()-2, this->height()-5), QPixmap(":/qss/infol"));*/
}
