#include "infowidget.h"
#include <QPainter>
#include<QPainterPath>
#include <QBrush>
#include <QPen>
#include <QPoint>
#define CH(a) QString::fromLocal8Bit(a)
Infowidget::Infowidget(QWidget *parent) :
    QWidget(parent)
{
}

Infowidget::~Infowidget()
{

}
void Infowidget::paintEvent(QPaintEvent *)
{
   // w=h=200;
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(0, 0, w,h);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::black));

 //   painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
  //  painter.drawLine(QPoint(1,1),QPoint(w,1));
  //  painter.drawLine(QPoint(1,1),QPoint(1,h));
 //   painter.drawLine(QPoint(1,h),QPoint(w,h));
  //  painter.drawLine(QPoint(w,1),QPoint(w,h));
  //  painter.drawLine(QPoint(w-20,5),QPoint(w-20,h-10));


    painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    painter.setFont(QFont("Times",15,QFont::Black));

    painter.drawText(QRect(w/3,13,w/3,20),Qt::AlignCenter,CH("机器人信息"));
    int hei=h-5;
    painter.setPen(QPen(Qt::green, 1, Qt::SolidLine));
    painter.setFont(QFont("Times",12,QFont::Bold));

    painter.drawText(QRect(w/4+10,hei/8+20,w/2,20),Qt::AlignLeft,CH("机器人ID: "));
    painter.drawText(QRect(w/2+10,hei/8+20,w/2,20),Qt::AlignLeft,terminalId);

    painter.drawText(QRect(w/4+10,hei*2/8+20,w,20),Qt::AlignLeft,CH("上报时间: "));
    painter.drawText(QRect(w/2+10,hei*2/8+20,w,20),Qt::AlignLeft,reportTime);

    painter.drawText(QRect(w/4+10,hei*3/8+20,w,20),Qt::AlignLeft,CH("当前位置: "));
    painter.drawText(QRect(w/2+10,hei*3/8+20,w,20),Qt::AlignLeft,pos);

    painter.drawText(QRect(w/4+10,hei*4/8+20,w,20),Qt::AlignLeft,CH("子位置  : "));
    painter.drawText(QRect(w/2+10,hei*4/8+20,w,20),Qt::AlignLeft,sonPos);

    painter.drawText(QRect(w/4+10,hei*5/8+20,w,20),Qt::AlignLeft,CH("数据类型: "));
    painter.drawText(QRect(w/2+10,hei*5/8+20,w,20),Qt::AlignLeft,datatype);

    painter.drawText(QRect(w/4+10,hei*6/8+20,w,20),Qt::AlignLeft,CH("数据    : "));
    painter.drawText(QRect(w/2+10,hei*6/8+20,w,20),Qt::AlignLeft,data);
}
