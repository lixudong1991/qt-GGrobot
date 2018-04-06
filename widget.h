#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include "main_widget.h"
#include "loginwidget.h"
#include "loading_widget.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
       void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
private slots:
        void doLog(int);
        void netErr();
        void showSettingDialog();
private:
    QStackedWidget *widstack;
    MainWidget *mainwid;
    Loginwidget *logwid;
    LoginDialog *login_dialog; //µÇÂ¼½çÃæ

    QList<Userterminal> *userDevices;
    QPoint move_point;
    bool mouse_press;
};

#endif // WIDGET_H
