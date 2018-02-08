#include "settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent)
    : Dialog(parent)
{
    resize(300, 300);
    dbserver_label=new QLabel(CH("IP地址:"));
    dbserver_label->setScaledContents(true);
    dbserver_label->setAlignment(Qt::AlignRight);
    dbport_label=new QLabel(CH("端口:"));
    dbport_label->setScaledContents(true);
    dbport_label->setAlignment(Qt::AlignRight);
    dbuser_label=new QLabel(CH("用户名:"));
    dbuser_label->setScaledContents(true);
    dbuser_label->setAlignment(Qt::AlignRight);
    dbpwd_label=new QLabel(CH("密码:"));
    dbpwd_label->setScaledContents(true);
    dbpwd_label->setAlignment(Qt::AlignRight);
    db_label=new QLabel(CH("数据库:"));
    db_label->setScaledContents(true);
    db_label->setAlignment(Qt::AlignRight);

    dbserverip=new QLineEdit();
    dbserverip->setFixedHeight(25);
    dbport=new QLineEdit();
    dbport->setFixedHeight(25);
    dbuser=new QLineEdit();
    dbuser->setFixedHeight(25);
    dbpwd=new QLineEdit();
    dbpwd->setEchoMode(QLineEdit::Password);
    dbpwd->setFixedHeight(25);
    db=new QLineEdit();
    db->setFixedHeight(25);

    ftpserver_label=new QLabel(CH("FTP地址:"));
    ftpserver_label->setScaledContents(true);
    ftpserver_label->setAlignment(Qt::AlignRight);
    ftpport_label=new QLabel(CH("端口:"));
    ftpport_label->setScaledContents(true);
    ftpport_label->setAlignment(Qt::AlignRight);
    ftpuser_label=new QLabel(CH("用户名:"));
    ftpuser_label->setScaledContents(true);
    ftpuser_label->setAlignment(Qt::AlignRight);
    ftppwd_label=new QLabel(CH("密码:"));
    ftppwd_label->setScaledContents(true);
    ftppwd_label->setAlignment(Qt::AlignRight);

    ftpserverip=new QLineEdit();
    ftpserverip->setFixedHeight(25);
    ftpport=new QLineEdit();
    ftpport->setFixedHeight(25);
    ftpuser=new QLineEdit();
    ftpuser->setFixedHeight(25);
    ftppwd=new QLineEdit();
    ftppwd->setEchoMode(QLineEdit::Password);
    ftppwd->setFixedHeight(25);

    pictimeConfigL=new QLabel(CH("刷新时间(秒):"));
    pictimeConfig=new QLineEdit();
    pictimeConfig->setFixedHeight(25);


    QSettings file("db.ini",QSettings::IniFormat);
    dbserverip->setText(file.value("database/ip").toString());
    dbport->setText(file.value("database/port").toString());
    dbuser->setText(file.value("database/user").toString());
    dbpwd->setText(file.value("database/pwd").toString());
    db->setText(file.value("database/db").toString());

    ftpserverip->setText(file.value("ftpserver/ip").toString());
    ftpport->setText(file.value("ftpserver/port").toString());
    ftpuser->setText(file.value("ftpserver/user").toString());
    ftppwd->setText(file.value("ftpserver/pwd").toString());
    pictimeConfig->setText(file.value("picture/refurbishtime").toString());

    setbt=new QPushButton(CH("保存"));
    closebt=new PushButton;
    closebt->setPicName(QString(":/sysButton/close"));

    QHBoxLayout *hb=new QHBoxLayout();
    title=new QWidget(this);
    QLabel* ti=new QLabel(CH("设置"));
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    ti->setPalette(pe);
    hb->addWidget(ti);
    hb->addStretch();
    hb->addWidget(closebt);
    hb->setSpacing(0);
    hb->setContentsMargins(10, 0, 0, 10);
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    title->setAutoFillBackground(true);
    title->setPalette(pal);
    title->setFixedHeight(30);
    title->setLayout(hb);

    dbconfig=new QWidget(this);
    ftpconfig=new QWidget(this);
    picTimeW=new QWidget(this);
    center=new QTabWidget(this);
    center->setFixedWidth(this->width());
    center->setStyleSheet("QTabWidget::pane{ border:none; }");
    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(title);
    title_layout->setSpacing(0);
    title_layout->setContentsMargins(5, 5, 5, 10);

    QVBoxLayout *center_layout=new QVBoxLayout();

    QGroupBox *dbconfigBox=new QGroupBox(CH("数据库配置"));
    QGroupBox *ftpconfigBox=new QGroupBox(CH("FTP配置"));
    QGroupBox *pictimeconfigBox=new QGroupBox(CH("图片刷新时间"));

    dbconfigBox->setFixedWidth(220);
    ftpconfigBox->setFixedWidth(220);
    pictimeconfigBox->setFixedWidth(220);

    QGridLayout *grid_layout = new QGridLayout();
    grid_layout->addWidget(dbserver_label,0,0);
    grid_layout->addWidget(dbserverip,0,1);
    grid_layout->addWidget(dbport_label,1,0);
    grid_layout->addWidget(dbport,1,1);
    grid_layout->addWidget(dbuser_label,2,0);
    grid_layout->addWidget(dbuser,2,1);
    grid_layout->addWidget(dbpwd_label,3,0);
    grid_layout->addWidget(dbpwd,3,1);
    grid_layout->addWidget(db_label,4,0);
    grid_layout->addWidget(db,4,1);
    grid_layout->setHorizontalSpacing(10);
    grid_layout->setVerticalSpacing(5);
    dbconfigBox->setLayout(grid_layout);

    QGridLayout *grid_layout1 = new QGridLayout();
    grid_layout1->addWidget(ftpserver_label,0,0);
    grid_layout1->addWidget(ftpserverip,0,1);
    grid_layout1->addWidget(ftpport_label,1,0);
    grid_layout1->addWidget(ftpport,1,1);
    grid_layout1->addWidget(ftpuser_label,2,0);
    grid_layout1->addWidget(ftpuser,2,1);
    grid_layout1->addWidget(ftppwd_label,3,0);
    grid_layout1->addWidget(ftppwd,3,1);
    grid_layout1->setHorizontalSpacing(10);
    grid_layout1->setVerticalSpacing(5);
    ftpconfigBox->setLayout(grid_layout1);


    QHBoxLayout *pictime=new QHBoxLayout();
    pictime->addWidget(pictimeConfigL);
    pictime->addWidget(pictimeConfig);
    pictimeconfigBox->setLayout(pictime);

    QHBoxLayout *pictab=new QHBoxLayout();
    pictab->addWidget(pictimeconfigBox);
    picTimeW->setLayout(pictab);
    QHBoxLayout *dbtab=new QHBoxLayout();
    dbtab->addWidget(dbconfigBox);
    dbconfig->setLayout(dbtab);
    QHBoxLayout *ftptab=new QHBoxLayout();
    ftptab->addWidget(ftpconfigBox);
    ftpconfig->setLayout(ftptab);

    center->addTab(dbconfig,CH("数据库配置"));
    center->addTab(ftpconfig,CH("FTP配置"));
    center->addTab(picTimeW,CH("图片刷新时间"));
    center_layout->addWidget(center);

    QHBoxLayout *savelayout = new QHBoxLayout();
    savelayout->addStretch();
    savelayout->addWidget(setbt);
    savelayout->setSpacing(0);
    savelayout->setContentsMargins(0, 0, 20, 10);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(center_layout);
    main_layout->addLayout(savelayout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

    connect(closebt, SIGNAL(clicked()), this, SLOT(close()));
    connect(setbt, SIGNAL(clicked()), this, SLOT(dbsave()));

    setLayout(main_layout);

}
SettingDialog::~SettingDialog()
{

}

 void SettingDialog::dbsave()
 {

         QSettings sets("db.ini", QSettings::IniFormat);
         sets.beginGroup("database");
         if(dbserverip->text().isEmpty())
         {
              box->setInfo(CH("提示信息"),CH("数据库服务器IP不能为空") , QPixmap(":/loginDialog/attention"), true);
              box->exec();
              return;
         }
         sets.setValue("ip", dbserverip->text());
         if(dbport->text().isEmpty())
         {
            dbport->setText("3306");
         }
         sets.setValue("port", dbport->text());

         if(dbuser->text().isEmpty())
         {
              box->setInfo(CH("提示信息"),CH("数据库用户名不能为空") , QPixmap(":/loginDialog/attention"), true);
              box->exec();
              return;
         }

         sets.setValue("user",dbuser->text());
         if(dbpwd->text().isEmpty())
         {
              box->setInfo(CH("提示信息"),CH("数据库密码不能为空") , QPixmap(":/loginDialog/attention"), true);
              box->exec();
              return;
         }
         sets.setValue("pwd", dbpwd->text());
         if(db->text().isEmpty())
         {
              box->setInfo(CH("提示信息"),CH("数据库名不能为空") , QPixmap(":/loginDialog/attention"), true);
              box->exec();
              return;
         }
         sets.setValue("db", db->text());
         sets.endGroup();

         sets.beginGroup("ftpserver");
         if(ftpserverip->text().isEmpty())
         {
              box->setInfo(CH("提示信息"),CH("FTP服务器IP不能为空") , QPixmap(":/loginDialog/attention"), true);
              box->exec();
              return;
         }
         sets.setValue("ip", ftpserverip->text());
         if(ftpport->text().isEmpty())
         {
            ftpport->setText("21");
         }
         sets.setValue("port", ftpport->text());
         if(ftpuser->text().isEmpty())
         {
              box->setInfo(CH("提示信息"),CH("FTP用户名不能为空") , QPixmap(":/loginDialog/attention"), true);
              box->exec();
              return;
         }
         sets.setValue("user",ftpuser->text());
         if(ftppwd->text().isEmpty())
         {
              box->setInfo(CH("提示信息"),CH("FTP密码不能为空") , QPixmap(":/loginDialog/attention"), true);
              box->exec();
              return;
         }
         sets.setValue("pwd", ftppwd->text());
         sets.endGroup();
         sets.beginGroup("picture");
         if(pictimeConfig->text().isEmpty())
         {
            pictimeConfig->setText("30");
         }
         sets.setValue("refurbishtime",pictimeConfig->text());
         sets.endGroup();
         hide();
         box->setInfo(CH("提示信息"),CH("保存成功") , QPixmap(":/loginDialog/attention"), true);
         box->exec();
         close();
 }
 void SettingDialog::paintEvent(QPaintEvent *event)
 {
     Dialog::paintEvent(event);
     int height = 69;
     QPainter painter(this);
     painter.setPen(Qt::NoPen);
     painter.setBrush(Qt::black);
     painter.drawRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width()-2*SHADOW_WIDTH, this->height()-2*SHADOW_WIDTH));
     painter.setBrush(Qt::white);
     painter.drawRect(QRect(SHADOW_WIDTH, height, this->width()-2*SHADOW_WIDTH, this->height()-height-SHADOW_WIDTH));
 }
