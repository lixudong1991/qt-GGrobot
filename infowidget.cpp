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
/***********************************************************************************
函数名:
函数描述:	 图像界面信息显示窗口数据绘制
输入参数:
输出参数:
返回值:
************************************************************************************/
void Infowidget::paintEvent(QPaintEvent *)
{
   // w=h=200;
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(0, 0, w,h);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::black));

    painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    painter.setFont(QFont("Times",15,QFont::Black));

    painter.drawText(QRect(w/3,13,w/3,20),Qt::AlignCenter,CH("机器人信息"));
    int hei=h-5;
    painter.setPen(QPen(Qt::green, 1, Qt::SolidLine));
    painter.setFont(QFont("Times",12,QFont::Bold));

    painter.drawText(QRect(w/4+10,hei/8+20,w/2,20),Qt::AlignLeft,CH("机器人ID: "));
    painter.drawText(QRect(w/4+10,hei*2/8+20,w,20),Qt::AlignLeft,CH("上报时间: "));
    painter.drawText(QRect(w/4+10,hei*3/8+20,w,20),Qt::AlignLeft,CH("设备名称: "));
    painter.drawText(QRect(w/4+10,hei*4/8+20,w,20),Qt::AlignLeft,CH("检测点  : "));
    painter.drawText(QRect(w/4+10,hei*5/8+20,w,20),Qt::AlignLeft,CH("检测类型: "));
    painter.drawText(QRect(w/4+10,hei*6/8+20,w,20),Qt::AlignLeft,CH("数据    : "));

    painter.drawText(QRect(w/2,hei/8+20,w/2,20),Qt::AlignLeft,terminalId);
    painter.drawText(QRect(w/2,hei*2/8+20,w,20),Qt::AlignLeft,reportTime);
    painter.drawText(QRect(w/2,hei*3/8+20,w,20),Qt::AlignLeft,pos);
    painter.drawText(QRect(w/2,hei*4/8+20,w,20),Qt::AlignLeft,sonPos);
    painter.drawText(QRect(w/2,hei*5/8+20,w,20),Qt::AlignLeft,datatype);
    painter.drawText(QRect(w/2,hei*6/8+20,w,20),Qt::AlignLeft,data);
}
