#ifndef ROUTEWIDGET_H
#define ROUTEWIDGET_H

#include "head.h"
#include <QPointF>
class RouteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RouteWidget(QWidget *parent = 0);
    ~RouteWidget();
    void paintEvent(QPaintEvent*);
    void setBackImg(int w ,int h,const QString &);
    void clearPoints()
    {
        afterPoints.clear();
    }

    void startPoint(int pointid,QList<int>*);
    int getFirstPoint()
    {
        return fristPiontId;
    }

private slots:
    void flashTimeout();
private:
    QList<int> afterPoints;
    QMap<int,QPointF> points;
    QTimer *flashTime;
    bool flashstatus=true;
    void parseXML(const QString &fname);
    int wid=0,hei=0;
    double r=0;
    int fristPiontId;
};

#endif // ROUTEWIDGET_H
