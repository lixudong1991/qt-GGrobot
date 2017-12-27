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

    QPoint move_point; //�ƶ��ľ���
    bool mouse_press; //����������
};

#endif // DIALOG_H
