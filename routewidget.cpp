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
������:    	setBackImg
��������:	���õ�ͼ����Ŀ�͸�,���ص�ͼ,��ȡ��ͼ�ϵ�����������ļ�
�������:   w:��ͼ����Ŀ�,h
�������:
����ֵ:
************************************************************************************/
void RouteWidget::setBackImg(int w ,int h,const QString &map)
{
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(QString("map/")+map+".png").scaled(QSize(w,h),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));             // ʹ��ƽ�������ŷ�ʽ
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
������:    	paintEvent
��������:	�����߹��ĵ���ɫ����Ϊ��ɫ,��ǰ����������Ϊ��ɫ,δ�߹��ĵ�����Ϊ��ɫ
�������:
�������:
����ֵ:
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
������:    	startPoint
��������:	������ͼ��ĳ�������˸
�������:   pointid:�����˵�ǰ�������id, ids:���������߹����id����
�������:
����ֵ:
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
 ������:    	flashTimeout
 ��������:	ÿ��0.5��ı��ͼ�ϻ����˵�ǰ���������ʾ״̬
 �������:
 �������:
 ����ֵ:
 **********************************************************************/
void RouteWidget::flashTimeout()
{
    flashstatus=!flashstatus;
    update();
}
/*************************************************
������:    	parseXML
��������:	������ͼ�ϵ������������ļ�
�������:  fname:�����ļ���·��
�������:
����ֵ:
*************************************************/
void RouteWidget::parseXML(const QString &fname)
{
    if(fname.isEmpty())
    return;

    QFile file(fname);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(nullptr, QString("error"),CH("�򿪵�ͼʧ��"));
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


