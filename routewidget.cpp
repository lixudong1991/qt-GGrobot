#include "routewidget.h"

RouteWidget::RouteWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
}
void RouteWidget::setBackImg(int w ,int h)
{
     qDebug()<<QString::number(w)<<" "<<QString::number(h);
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
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(QPoint(50,50),5,5);

}
