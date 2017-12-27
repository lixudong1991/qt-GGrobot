#ifndef ROUTEWIDGET_H
#define ROUTEWIDGET_H

#include "head.h"


class RouteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RouteWidget(QWidget *parent = 0);
    ~RouteWidget();
    void paintEvent(QPaintEvent*);
    void setBackImg(int w ,int h);
private slots:

private:

};

#endif // ROUTEWIDGET_H
