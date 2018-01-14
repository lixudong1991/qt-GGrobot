#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : Dialog(parent)
{
    resize(280, 240);
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
    login_layout->addStretch();
    login_layout->addWidget(login_button);
    login_layout->setSpacing(0);
    login_layout->setContentsMargins(0, 0, 20, 20);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(login_stacked_layout);
    main_layout->addLayout(login_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

    connect(close_button, SIGNAL(clicked()), this, SLOT(close()));
    connect(login_button, SIGNAL(clicked()), this, SLOT(verify()));
    connect(&logt,SIGNAL(logstatus(int)),this,SLOT(logstatus(int)));
    setLayout(main_layout);
    translateLanguage();



}
LoginDialog::~LoginDialog()
{

}
void LoginDialog::inittitlewid()
{
    title_label = new QLabel(CH("µÇÂ½"));
    title_label->setAlignment(Qt::AlignBottom);

    close_button = new PushButton();
    close_button->setPicName(QString(":/sysButton/close"));

    QHBoxLayout *title_layout = new QHBoxLayout();
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    title_label->setPalette(pe);
    title_layout->addWidget(title_label);
    title_layout->addStretch();
    title_layout->addWidget(close_button);
    title_layout->setSpacing(0);
    title_layout->setContentsMargins(10, 0, 0, 10);

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    title_wid->setAutoFillBackground(true);
    title_wid->setPalette(pal);
    title_wid->setFixedHeight(30);
    title_wid->setLayout(title_layout);
}

void LoginDialog::initloginwid()
{
    account_label = new QLabel();
    password_label = new QLabel();
    login_button = new QPushButton();

    password_line_edit = new QLineEdit();
    remember_check_box = new QCheckBox();
    auto_login_check_box = new QCheckBox();

    account_combo_box = new QComboBox();
    list_widget = new QListWidget();
    account_combo_box->setModel(list_widget->model());
    account_combo_box->setView(list_widget);
    account_combo_box->setEditable(true);

    account_label->setScaledContents(true);
    password_label->setScaledContents(true);
    account_label->setAlignment(Qt::AlignRight);
    password_label->setAlignment(Qt::AlignRight);
    password_line_edit->setEchoMode(QLineEdit::Password);

    account_combo_box->setFixedSize(190,25);
    password_line_edit->setFixedSize(190,25);

    login_button->setFixedSize(60, 25);


    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addWidget(remember_check_box);
 //   h_layout->addWidget(auto_login_check_box);
    h_layout->addStretch();
    h_layout->setSpacing(40);
    h_layout->setContentsMargins(0, 0, 0, 0);

    QGridLayout *grid_layout = new QGridLayout();


    grid_layout->addWidget(account_label, 0, 0);
    grid_layout->addWidget(account_combo_box, 0, 1);
    grid_layout->addWidget(password_label, 1, 0);
    grid_layout->addWidget(password_line_edit, 1, 1);
    grid_layout->addLayout(h_layout, 2, 1);
    grid_layout->setHorizontalSpacing(5);
    grid_layout->setVerticalSpacing(10);
    grid_layout->setContentsMargins(10, 0, 0, 0);
    login_widget->setLayout(grid_layout);

    QSettings sets("user.ini", QSettings::IniFormat);
    if(sets.contains("user/username")&& sets.contains("user/password"))
    {
        remember_check_box->setChecked(true);
        account_combo_box->lineEdit()->setText(sets.value("user/username").toString());
        password_line_edit->setText(sets.value("user/password").toString());
    }
    else
    {
         remember_check_box->setChecked(false);
    }
}
void LoginDialog::translateLanguage()
{

    close_button->setToolTip(CH("¹Ø±Õ"));

    account_label->setText(CH("ÓÃ»§Ãû:"));
    password_label->setText(CH("ÃÜÂë:"));

    login_button->setText(CH("µÇÂ¼"));
    remember_check_box->setText(CH("¼Ç×¡ÃÜÂë"));
   // auto_login_check_box->setText(CH("×Ô¶¯µÇÂ¼"));


}
void LoginDialog::verify()
{
    QSettings sets("user.ini", QSettings::IniFormat);
    if(remember_check_box->isChecked())
    {
        sets.beginGroup("user");
        sets.setValue("username", account_combo_box->lineEdit()->text());
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
            QMessageBox::critical(this,CH("´íÎó"),CH("ÇëÅäÖÃFTP·þÎñÆ÷ÐÅÏ¢"));
            return;
    }
     if(!file.contains("database/ip")||
        !file.contains("database/user")||
        !file.contains("database/pwd")||
        !file.contains("database/db"))
      {
            QMessageBox::critical(this,CH("´íÎó"),CH("ÇëÅäÖÃÊý¾Ý¿âÐÅÏ¢"));
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
    if(current_widget != loading_widget)
    {
        login_button->setText(CH("È¡Ïû"));
        login_stacked_layout->setCurrentWidget(loading_widget);
        loading_widget->setAccount(account_combo_box->lineEdit()->text());      
        loading_widget->start(true);     

            logt.ip=file.value("database/ip").toString();
            logt.port=file.value("database/port").toInt();
            logt.username=file.value("database/user").toString();
            logt.password=file.value("database/pwd").toString();
            logt.dbna=file.value("database/db").toString();
            logt.user=account_combo_box->lineEdit()->text();
            logt.pwd=password_line_edit->text();
            logt.start();
    }
    else
    {
        login_button->setText(CH("µÇÂ¼"));
        loading_widget->start(false);
        login_stacked_layout->setCurrentWidget(login_widget);
        if(logt.isRunning())
        {
            logt.terminate();
        }
    }

}
void LoginDialog::logstatus(int status)
{
    loading_widget->start(false);
    if(status==-1)
    {
          login_button->setHidden(true);
          msg->setText(CH("µÇÂ½Ê§°Ü"));
          login_stacked_layout->setCurrentWidget(logmsg);
          islog=false;
          return;
    }
    emit doLogin();
    login_button->setEnabled(false);
    islog=true;
    close();
}

void LoginDialog::closeEvent(QCloseEvent* e)
{
    login_stacked_layout->setCurrentWidget(login_widget);
    login_button->setText(CH("µÇÂ¼"));
    login_button->setHidden(false);
    e->accept();
}

