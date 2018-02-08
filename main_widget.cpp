#include "main_widget.h"
#include <QProcess>
MainWidget::MainWidget(QWidget *parent)
    : QDialog(parent)
{
    ILog4zManager::getRef().start();
    setWindowFlags(Qt::FramelessWindowHint);
 //   setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoBackground);
    setWindowIcon(QIcon(":/qss/wall"));
    mouse_press = false;


    QDesktopWidget *d=QApplication::desktop();
    QRect sc=d->screenGeometry();
    setFixedSize(sc.width(),sc.height());

    userDevices=new QList<Userterminal>();


    statked_widget = new QStackedWidget();
    title_widget=new TitleWidget();

    Cloud_widget=new CloudWidget();
    Cloud_widget->setUserDevices(userDevices);
    exprot_widget=new ExportWidget();
    exprot_widget->setUserDevices(userDevices);

    alarmwidget=new AlarmWidget();
    alarmwidget->setUserDevices(userDevices);

    login_dialog=new LoginDialog();
    login_dialog->setTreadDevices(userDevices);

    main_menu=new MainMenu();

    connect(title_widget, SIGNAL(showMainMenu()), this, SLOT(showMainMenu()));
    connect(title_widget, SIGNAL(closeWidget()), this, SLOT(close()));
    connect(title_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(title_widget, SIGNAL(turnPage(int)), this, SLOT(turnPage(int)));

    connect(main_menu, SIGNAL(showlogindia()), this, SLOT(showLoginDialog()));
    connect(main_menu, SIGNAL(showdbset()), this, SLOT(showSettingDialog()));
    connect(main_menu, SIGNAL(showdbManage()), this, SLOT(showdbManage()));

    connect(login_dialog,SIGNAL(doLogin()),this,SLOT(doLog()));

    connect(Cloud_widget,SIGNAL(exitprocess()),this,SLOT(close()));
    connect(Cloud_widget,SIGNAL(haveAlarm(int)),this,SLOT(setAlarmstatus(int)));
    connect(alarmwidget,SIGNAL(noAlarm()),this,SLOT(resetAlarmstatus()));

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    statked_widget->setPalette(palette);
    statked_widget->setAutoFillBackground(true);


    statked_widget->addWidget(Cloud_widget);
    statked_widget->addWidget(exprot_widget);
    statked_widget->addWidget(alarmwidget);

    QVBoxLayout *center_layout = new QVBoxLayout();
    center_layout->addWidget(statked_widget);
    center_layout->setSpacing(0);
    center_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_widget);
    main_layout->addLayout(center_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

    setLayout(main_layout);

    Cloud_widget->setLabelSize(sc.width(),sc.height()-100);
    Cloud_widget->update();
    exprot_widget->setLabelSize(sc.width(),sc.height()-100);
    alarmwidget->setLabelSize(sc.width(),sc.height()-100);
}

MainWidget::~MainWidget()
{
    delete userDevices;
}
void MainWidget::turnPage(int current_page)
{
    if(current_page == 0)
    {
        statked_widget->setCurrentWidget(Cloud_widget);
    }
    else if(current_page == 1)
    {   
          statked_widget->setCurrentWidget(alarmwidget);
    }
    else
    {
        statked_widget->setCurrentWidget(exprot_widget);
    }
}

void MainWidget::showMainMenu()
{
    //设置主菜单出现的位置
    QPoint p = rect().topRight();
    p.setX(p.x() - 60);
    p.setY(p.y() + 30);
    main_menu->exec(this->mapToGlobal(p));
}
void MainWidget::showLoginDialog()
{
    login_dialog->exec();
}
void MainWidget::showSettingDialog()
{
    SettingDialog dbsetting;
    dbsetting.exec();
}
void MainWidget::showdbManage()
{
    QProcess *dbMangerProcess = new QProcess(this);
    dbMangerProcess ->start("WallRegister.exe");
}

void MainWidget::doLog()
{
   Cloud_widget->initTerminal();
   exprot_widget->initData();
   alarmwidget->initDevices();
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }

    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void MainWidget::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}

void MainWidget::setAlarmstatus(int id)
{
    title_widget->setAlarmBackground(true);
    alarmwidget->setCurrentDevice(id);
}

void MainWidget::resetAlarmstatus()
{
 //   alarmwidget->setCurrentDevice(device);
     title_widget->setAlarmBackground(false);
}
