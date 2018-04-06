#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "logindialog.h"
class Loginwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Loginwidget(QWidget *parent = 0);
    ~Loginwidget();
protected:
    void paintEvent(QPaintEvent *);
private:

};

#endif // LOGINWIDGET_H
