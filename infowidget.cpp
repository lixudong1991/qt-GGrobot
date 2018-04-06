#include "infowidget.h"
#include <QPainter>
#include<QPainterPath>
#include <QBrush>
#include <QPen>
#include <QPoint>
#include "log4z.h"
using namespace zsummer::log4z;
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
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(0, 0, w,h);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::black));

    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine));
    float weith=w*4/7;
    float weith1=w*3/7;
    painter.drawLine(weith,0,weith,h);
    painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    painter.setFont(QFont("Times",13,QFont::Black));

    float fonthei=h*0.063;
    painter.drawText(QRectF(weith/3,h*0.041,weith/3,fonthei),Qt::AlignCenter,CH("检测数据"));
    painter.setFont(QFont("Times",11,QFont::Black));
    painter.drawText(QRectF(weith+weith1/4,h*0.037,weith1/2,fonthei),Qt::AlignCenter,CH("机器人信息"));
    float hei=h-fonthei/4;
    painter.setPen(QPen(Qt::green, 1, Qt::SolidLine));
    painter.setFont(QFont("Times",11,QFont::Bold));

    float wei=weith/6;
    painter.drawText(QRectF(wei,hei/8+fonthei,weith*2/5,fonthei),Qt::AlignLeft,CH("机器人ID:"));
    painter.drawText(QRectF(wei,hei*2/8+fonthei,weith*2/5,fonthei),Qt::AlignLeft,CH("上报时间:"));
    painter.drawText(QRectF(wei,hei*3/8+fonthei,weith*2/5,fonthei),Qt::AlignLeft,CH("设备名称:"));
    painter.drawText(QRectF(wei,hei*4/8+fonthei,weith*2/5,fonthei),Qt::AlignLeft,CH("检 测 点:"));
    painter.drawText(QRectF(wei,hei*5/8+fonthei,weith*2/5,fonthei),Qt::AlignLeft,CH("检测类型:"));
    painter.drawText(QRectF(wei,hei*6/8+fonthei,weith*2/5,fonthei),Qt::AlignLeft,CH("数    据:"));

    float we=weith/2-h*0.1;
    painter.drawText(QRectF(we,hei/8+fonthei,weith*3/5,fonthei),Qt::AlignLeft,terminalId);
    painter.drawText(QRectF(we,hei*2/8+fonthei,weith*3/5,fonthei),Qt::AlignLeft,reportTime);
    painter.drawText(QRectF(we,hei*3/8+fonthei,weith*3/5,fonthei),Qt::AlignLeft,pos);
    painter.drawText(QRectF(we,hei*4/8+fonthei,weith*3/5,fonthei),Qt::AlignLeft,sonPos);
    painter.drawText(QRectF(we,hei*5/8+fonthei,weith*3/5,fonthei),Qt::AlignLeft,datatype);
    painter.drawText(QRectF(we,hei*6/8+fonthei,weith*3/5,fonthei),Qt::AlignLeft,data);

     painter.setFont(QFont("Times",10,QFont::Bold));
//    float wei1=weith+weith1/7;
//    float fonthei1=fonthei*2/3;
//    painter.drawText(QRectF(wei1,hei/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("电      流:"));
//    painter.drawText(QRectF(wei1,hei*2/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("电      压:"));
//    painter.drawText(QRectF(wei1,hei*3/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("剩 余电 量:"));
//    painter.drawText(QRectF(wei1,hei*4/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("机器人状态:"));
//    painter.drawText(QRectF(wei1,hei*5/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("前  雷  达:"));
//    painter.drawText(QRectF(wei1,hei*6/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("后  雷  达:"));
//    painter.drawText(QRectF(wei1,hei*7/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("前 磁导 航:"));
//    painter.drawText(QRectF(wei1,hei*8/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("后 磁导 航:"));
//    painter.drawText(QRectF(wei1,hei*9/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("地标读卡器:"));
//    painter.drawText(QRectF(wei1,hei*10/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("自动门状态:"));
//    painter.drawText(QRectF(wei1,hei*11/13+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("充电器状态: "));
      float wei1=weith+weith1/14;
      float fonthei1=fonthei;
      painter.drawText(QRectF(wei1,hei/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("上报时间:"));
      painter.drawText(QRectF(wei1,hei*2/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("电池电流:"));
      painter.drawText(QRectF(wei1,hei*3/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("电池电压:"));
      painter.drawText(QRectF(wei1,hei*4/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("电池电量:"));
      painter.drawText(QRectF(wei1,hei*5/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("工作模式:"));
      painter.drawText(QRectF(wei1,hei*6/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,CH("当前状态:"));

       float we1=weith+weith1/2-weith1/6;
      painter.drawText(QRectF(we1,hei/8+fonthei1,weith,fonthei1),Qt::AlignLeft,statsTime);
      painter.drawText(QRectF(we1,hei*2/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,electricitys);
      painter.drawText(QRectF(we1,hei*3/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,voltage);
      painter.drawText(QRectF(we1,hei*4/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft,electricResidue);
      painter.drawText(QRectF(we1,hei*5/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft, robotWorkMode);
      painter.drawText(QRectF(we1,hei*6/8+fonthei1,weith*2/5,fonthei1),Qt::AlignLeft, robotStatus);

}
