#include "routewidget.h"

RouteWidget::RouteWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
}
void RouteWidget::setBackImg(int w ,int h)
{
    this->setAutoFillBackground(true); // ���Ҫ����, ���������ʾ��������ͼ.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":/qss/infol").scaled(QSize(w,h),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // ʹ��ƽ�������ŷ�ʽ
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
