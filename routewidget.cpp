#include "routewidget.h"
#include <QDomComment>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
RouteWidget::RouteWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    flashTime=new QTimer;
    connect(flashTime,SIGNAL(timeout()),this,SLOT(flashTimeout()));
}
/***********************************************************************************
函数名:    	setBackImg
函数描述:	设置地图区域的宽和高,加载地图,读取地图上点的坐标配置文件
输入参数:   w:地图区域的宽,h
输出参数:
返回值:
************************************************************************************/
void RouteWidget::setBackImg(int w ,int h,const QString &map)
{
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(QString("map/")+map+".png").scaled(QSize(w,h),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette); 
    afterPoints.clear();
    points.clear();
    flashTime->stop();
    flashstatus=true;
    wid=w;
    hei=h;
    r=h*0.01;
    parseXML(QString("map/")+map+".xml");
    fristPiontId=points.keys().first();
    update();
}

RouteWidget::~RouteWidget()
{
}
/***************************************************************************************************
函数名:    	paintEvent
函数描述:	将已走过的点颜色设置为黄色,当前所处点设置为红色,未走过的点设置为蓝色
输入参数:
输出参数:
返回值:
****************************************************************************************************/
void RouteWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);
    if(points.isEmpty())
    {
        return;
    }
    QMap<int,QPointF>::iterator iter;
    for(iter=points.begin(); iter!=points.end(); ++iter)
    {
       QPointF &p=iter.value();
       painter.drawEllipse(QPointF(wid*p.rx(),hei*(1.0-p.ry())),r,r);
    }
    if(afterPoints.isEmpty())
    {
        return;
    }
    painter.setBrush(Qt::green);
    QMap<int,QPointF>::iterator mi;
    for(int i=0;i<afterPoints.size()-1;i++)
    {
          mi=points.find(afterPoints.at(i));
          if(mi != points.end())
          {
              QPointF &p=mi.value();
              painter.drawEllipse(QPointF(wid*p.rx(),hei*(1.0-p.ry())),r,r);
          }
    }
    if(flashstatus)
    {
      painter.setBrush(Qt::yellow);
    }else{
      painter.setBrush(Qt::blue);
    }
    mi=points.find(afterPoints.last());
    if(mi != points.end())
    {
        QPointF &p=mi.value();
        painter.drawEllipse(QPointF(wid*p.rx(),hei*(1.0-p.ry())),r,r);
    }
}
/********************************************************************************
函数名:    	startPoint
函数描述:	启动地图上某个点的闪烁
输入参数:   pointid:机器人当前所处点的id, ids:机器人已走过点的id集合
输出参数:
返回值:
*********************************************************************************/
 void RouteWidget::startPoint(int pointid,QList<int>*ids)
{
    if(flashTime->isActive())
    {
        flashTime->stop();
        flashstatus=true;
    }
    if(!points.isEmpty())
    {
        if(pointid==fristPiontId)
        {
            afterPoints.clear();
        }else{
           for(int i=0;i<ids->size();i++)
           {
              afterPoints.append(ids->at(i));
           }
        }
        QMap<int,QPointF>::iterator mi;
        mi=points.find(pointid);
        if(mi != points.end())
        {
             afterPoints.append(pointid);
        }
    }
    if(afterPoints.size()>0)
    {
         flashTime->start(500);
    }
 }
 /*********************************************************************
 函数名:    	flashTimeout
 函数描述:	每隔0.5秒改变地图上机器人当前所处点的显示状态
 输入参数:
 输出参数:
 返回值:
 **********************************************************************/
void RouteWidget::flashTimeout()
{
    flashstatus=!flashstatus;
    update();
}
/*************************************************
函数名:    	parseXML
函数描述:	解析地图上点的坐标的配置文件
输入参数:  fname:配置文件的路径
输出参数:
返回值:
*************************************************/
void RouteWidget::parseXML(const QString &fname)
{
    if(fname.isEmpty())
    return;

    QFile file(fname);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(nullptr, QString("error"),CH("打开地图失败"));
        return;
    }

    QDomDocument domDocument;
    QString error;
    int row = 0, column = 0;
    if(!domDocument.setContent(&file, false, &error, &row, &column)) {
        QMessageBox::information(nullptr, QString("Error"),
                                 QString("parse file failed at line row and column") +
                                 QString::number(row, 10) + QString(",") + QString::number(column, 10));
        file.close();
        return;
    }

    if(domDocument.isNull()) {
        QMessageBox::information(nullptr, QString("title"),QString("document is null!"));

        file.close();
        return;
    }

    const QDomElement domElement = domDocument.documentElement();

    const QString domElementTagName = domElement.tagName();

    if (domElementTagName != "routemap") {
        QMessageBox::information(nullptr, QString("title"),
                                 QString("Root Name is wrong!"));
        file.close();
        return;
    }
    const QDomNodeList pointList = domElement.childNodes();
    for(int i=0;i<pointList.count();i++)
    {
        const QDomNode p =pointList.item(i);
        if(!p.isNull())
        {
            QDomElement elementson = p.toElement();
            if(!elementson.isNull()) {
                if (elementson.hasAttribute("id"))
                {
                    int pid=elementson.attributeNode("id").value().toInt();
                    const QDomNode fristNode =elementson.firstChild();
                    const QDomNode lastNode =elementson.lastChild();
                    if(!fristNode.isNull()&&!lastNode.isNull())
                    {
                        const QDomElement fristElement = fristNode.toElement();
                        const QDomElement lastElement = lastNode.toElement();
                        if(!fristElement.isNull()&&!lastElement.isNull())
                        {
                            int xp=-1,yp=-1;
                            const QString tagname=fristElement.tagName();
                            const QString tagval=fristElement.text();
                            if(!tagval.isEmpty())
                            {
                                if(tagname=="x")
                                {
                                    xp=tagval.toInt();
                                }else{
                                    yp=tagval.toInt();
                                }
                            }
                            const QString tagname1=lastElement.tagName();
                            const QString tagval1=lastElement.text();
                            if(!tagval1.isEmpty())
                            {
                                if(tagname1=="x")
                                {
                                    xp=tagval1.toInt();
                                }else{
                                    yp=tagval1.toInt();
                                }
                            }
                            if(xp!=-1&&yp!=-1)
                            {
                                points.insert(pid,QPointF(((double)xp)/1000.0,((double)yp)/1000.0));
                            }
                        }

                    }
                }
            }
        }
    }
    LOGI("points size: "<< points.size()<<" : "<<r);
}


