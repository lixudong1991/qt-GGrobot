#ifndef DIALOG_H
#define DIALOG_H

#include "head.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:

    QPoint move_point; //移动的距离
    bool mouse_press; //按下鼠标左键
};

#endif // DIALOG_H
