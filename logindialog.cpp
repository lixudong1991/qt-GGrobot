 #include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    resize(340, 230);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    loading_widget = new LoadingWidget(this);
    login_widget = new QWidget(this);
    title_wid= new QWidget(this);
    logmsg=new QWidget(this);
    msg=new QLabel();
    QHBoxLayout *lmsg=new QHBoxLayout(logmsg);
    lmsg->addWidget(msg);
    lmsg->setContentsMargins(130,20,20,20);

    inittitlewid();
    initloginwid();

    login_stacked_layout = new QStackedLayout();
    login_stacked_layout->addWidget(login_widget);
    login_stacked_layout->addWidget(loading_widget);
    login_stacked_layout->addWidget(logmsg);
    login_stacked_layout->setCurrentWidget(login_widget);

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(title_wid);
    title_layout->setSpacing(0);
    title_layout->setContentsMargins(5, 5, 5, 5);

    QHBoxLayout *login_layout = new QHBoxLayout();
     login_layout->addWidget(configbt);
    login_layout->addStretch();
    login_layout->addWidget(login_button);
    login_layout->setSpacing(0);
    login_layout->setContentsMargins(54, 12, 43, 18);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(login_stacked_layout);
    main_layout->addLayout(login_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

    connect(close_button, SIGNAL(clicked()), this, SLOT(close()));
    connect(login_button, SIGNAL(clicked()), this, SLOT(verify()));
    connect(configbt,SIGNAL(clicked(bool)),this,SIGNAL(showdbset()));
    connect(&logt,SIGNAL(logstatus(int)),this,SLOT(logstatus(int)));
    setLayout(main_layout);
    translateLanguage();
    setStyleSheet("QWidget{border-top-left-radius:5px;border-top-right-radius:5px;border-bottom-left-radius:5px, border-bottom-right-radius:5px}");
}
LoginDialog::~LoginDialog()
{
}
void LoginDialog::inittitlewid()
{

    close_button = new PushButton();
    close_button->setPicName(QString(":/sysButton/close"));

    QHBoxLayout *title_layout = new QHBoxLayout();
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    title_layout->addStretch();
    title_layout->addWidget(close_button,0,Qt::AlignTop);
    title_layout->setSpacing(0);
    title_layout->setContentsMargins(0, 0, 0, 0);

    title_wid->setFixedHeight(25);
    title_wid->setLayout(title_layout);
}

void LoginDialog::initloginwid()
{
    login_button = new QPushButton();
    configbt = new QPushButton();

    password_line_edit = new QLineEdit();
    remember_check_box = new QCheckBox();

    account_combo_box = new QLineEdit();
    account_combo_box->setFont(QFont(tr("Microsoft YaHei"), 13));
   // account_combo_box->setStyleSheet("background:rgba(255,0,0,0);border-radius:0px;");
    list_widget = new QListWidget();
    password_line_edit->setEchoMode(QLineEdit::Password);
    //password_line_edit->setStyleSheet("background:rgba(255,0,0,0);border-radius:0px;");
    account_combo_box->setFixedSize(208,25);
    password_line_edit->setFixedSize(208,25);

    login_button->setFixedSize(62, 30);
    configbt->setFixedSize(62,30);
    QVBoxLayout *grid_layout=new QVBoxLayout();
    grid_layout->setSpacing(7);
    grid_layout->addWidget(account_combo_box);
    grid_layout->addWidget(password_line_edit);
    grid_layout->addWidget(remember_check_box);
    grid_layout->setContentsMargins(84, 4, 0, 0);
    login_widget->setLayout(grid_layout);

    QSettings sets("user.ini", QSettings::IniFormat);
    if(sets.contains("user/username")&& sets.contains("user/password"))
    {
        remember_check_box->setChecked(true);
        account_combo_box->setText(sets.value("user/username").toString());
        password_line_edit->setText(sets.value("user/password").toString());
    }
    else
    {
         remember_check_box->setChecked(false);
    }
}
void LoginDialog::translateLanguage()
{
    close_button->setToolTip(CH("关闭"));
    login_button->setText(CH("登录"));
    configbt->setText(CH("配置"));
    remember_check_box->setText(CH("记住密码"));
}
/***********************************************************************************
函数名:
函数描述:	 启动登陆查询线程
输入参数:
输出参数:
返回值:
************************************************************************************/
void LoginDialog::verify()
{
    QSettings sets("user.ini", QSettings::IniFormat);
    if(remember_check_box->isChecked())
    {
        sets.beginGroup("user");
        sets.setValue("username", account_combo_box->text());
        sets.setValue("password",password_line_edit->text() );
        sets.endGroup();
    }
    else
    {
        sets.remove("user/username");
        sets.remove("user/password");
    }
    QSettings file("db.ini",QSettings::IniFormat);
    if(!file.contains("ftpserver/ip")|| ! file.contains("ftpserver/user")|| !file.contains("ftpserver/pwd"))
     {
            QMessageBox::critical(this,CH("错误"),CH("请配置FTP服务器信息"));
            return;
    }
     if(!file.contains("database/ip")|| !file.contains("database/user")|| !file.contains("database/pwd")||
        !file.contains("database/db"))
      {
            QMessageBox::critical(this,CH("错误"),CH("请配置数据库信息"));
            return;
       }
     if(!file.contains("ftpserver/port"))
     {
         file.beginGroup("ftpserver");
         file.setValue("port","21");
         file.endGroup();
     }
     if( !file.contains("database/port"))
     {
         file.beginGroup("database");
         file.setValue("port","3306");
         file.endGroup();
     }
     if(!file.contains("picture/refurbishtime"))
     {
           file.beginGroup("picture");
           file.setValue("refurbishtime","30");
           file.endGroup();
     }
     if(islog)
     {
         close();
         return;
     }
    QWidget *current_widget = login_stacked_layout->currentWidget();
    if(current_widget == login_widget)
    {
        login_button->setText(CH("取消"));
        login_stacked_layout->setCurrentWidget(loading_widget);
        loading_widget->setAccount(account_combo_box->text());
        loading_widget->start(true);     

            logt.ip=file.value("database/ip").toString();
            logt.port=file.value("database/port").toInt();
            logt.username=file.value("database/user").toString();
            logt.password=file.value("database/pwd").toString();
            logt.dbna=file.value("database/db").toString();
            logt.user=username=account_combo_box->text();
            logt.pwd=password=password_line_edit->text();
            logt.start();
    }
    else
    {
        login_button->setText(CH("登录"));
        login_stacked_layout->setCurrentWidget(login_widget);
        if(logt.isRunning())
        {
            logt.terminate();
        }
    }

}
/***********************************************************************************
函数名:
函数描述:	 登陆状态响应函数
输入参数:
输出参数:
返回值:
************************************************************************************/
void LoginDialog::logstatus(int status)
{
    loading_widget->start(false);
    emit doLogin(status);
    if(status==-1)
    {
          login_button->setText(CH("返回"));
          msg->setText(CH("登陆失败"));
          login_stacked_layout->setCurrentWidget(logmsg);
          islog=false;
    }else
    {
          login_button->setEnabled(false);
          islog=true;
          close();
    }

}

void LoginDialog::closeEvent(QCloseEvent* e)
{
    login_stacked_layout->setCurrentWidget(login_widget);
    login_button->setText(CH("登录"));
    login_button->setHidden(false);
    if(!islog)
    {
        emit exitMain();
    }
    e->accept();
}
 void LoginDialog::reLogin()
 {
    islog=false;
    login_button->setEnabled(true);
    login_stacked_layout->setCurrentWidget(login_widget);
    verify();
 }
 void LoginDialog::paintEvent(QPaintEvent *)
 {
     QPainter painter(this);
     painter.setPen(Qt::NoPen);
     painter.setBrush(Qt::white);
     painter.drawPixmap(QRect(0, 0, this->width(), this->height()), QPixmap(":/qss/log"));
 }
