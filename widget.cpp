#include "widget.h"
#include "settingdialog.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
 //   setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoBackground);
    setWindowIcon(QIcon(":/qss/wall"));

    QDesktopWidget *d=QApplication::desktop();
    QRect sc=d->screenGeometry();
    setFixedSize(sc.width(),sc.height());
    mouse_press = false;

    widstack = new QStackedWidget();
    mainwid =new MainWidget();
    logwid= new Loginwidget();
    login_dialog=new LoginDialog(this);
    connect(login_dialog,SIGNAL(exitMain()),this,SLOT(close()));
    connect(login_dialog,SIGNAL(doLogin(int)),this,SLOT(doLog(int)));
    connect(login_dialog,SIGNAL(showdbset()),this,SLOT(showSettingDialog()));
    connect(mainwid,SIGNAL(exitMain()),this,SLOT(close()));
    connect(mainwid,SIGNAL(netErr()),this,SLOT(netErr()));
    connect(mainwid,SIGNAL(showMin()),this,SLOT(showMinimized()));
    widstack->addWidget(mainwid);
    widstack->addWidget(logwid);
    widstack->setCurrentWidget(logwid);

    QVBoxLayout *mainla=new QVBoxLayout();
    mainla->addWidget(widstack);
    mainla->setContentsMargins(0,0,0,0);

    setLayout(mainla);
    userDevices=new QList<Userterminal>();
    login_dialog->setTreadDevices(userDevices);
    mainwid->setUserDevice(userDevices);
    login_dialog->show();
}

Widget::~Widget()
{
    delete userDevices;
}
 void Widget::doLog(int s)
 {
    if(s!=-1)
    {
        widstack->setCurrentWidget(mainwid);
        mainwid->doLog();
    }
 }
 void Widget::showSettingDialog()
 {
   //  login_dialog->hide();
     SettingDialog dbsetting;
     dbsetting.exec();
    // login_dialog->show();
 }
void Widget::netErr()
{
    widstack->setCurrentWidget(logwid);
    login_dialog->show();
    login_dialog->reLogin();
}
void  Widget::mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }
    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void Widget::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }

}
