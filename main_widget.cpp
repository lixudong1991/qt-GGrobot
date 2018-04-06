#include "main_widget.h"
#include <QProcess>
MainWidget::MainWidget(QWidget *parent)
    : QDialog(parent)
{

    setWindowFlags(Qt::FramelessWindowHint);
 //   setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_NoBackground);
  //  setWindowIcon(QIcon(":/qss/wall"));
    title_widget=new TitleWidget();

    QDesktopWidget *d=QApplication::desktop();
    QRect sc=d->screenGeometry();
    setFixedSize(sc.width(),sc.height());

    statked_widget = new QStackedWidget();

    Cloud_widget=new CloudWidget();

    exprot_widget=new ExportWidget();
    alarmwidget=new AlarmWidget();

    main_menu=new MainMenu();

    connect(title_widget, SIGNAL(showMainMenu()), this, SLOT(showMainMenu()));
    connect(title_widget, SIGNAL(closeWidget()), this, SIGNAL(exitMain()));
    connect(title_widget, SIGNAL(showMin()), this, SIGNAL(showMin()));
    connect(title_widget, SIGNAL(turnPage(int)), this, SLOT(turnPage(int)));

    connect(main_menu, SIGNAL(showdbManage()), this, SLOT(showdbManage()));

    connect(Cloud_widget,SIGNAL(exitprocess()),this,SLOT(neterror()));
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
    //login_dialog->exec();
}
void MainWidget::showSettingDialog()
{
  //  SettingDialog dbsetting;
   // dbsetting.exec();
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
void  MainWidget::setUserDevice(QList<Userterminal> * devices)
{
         Cloud_widget->setUserDevices(devices);
         exprot_widget->setUserDevices(devices);
         alarmwidget->setUserDevices(devices);
 }


void MainWidget::setAlarmstatus(int id)
{
    title_widget->setAlarmBackground(true);
    alarmwidget->setCurrentDevice(id);
}

void MainWidget::resetAlarmstatus()
{
     title_widget->setAlarmBackground(false);
}
void MainWidget::neterror()
{
    exprot_widget->netError();
    alarmwidget->netError();
    emit netErr();
    LOGI("MainWidget neterr");
}
