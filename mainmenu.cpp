#include "mainmenu.h"
MainMenu::MainMenu(QWidget *widget)
    : QMenu(widget)
{
   createActions();
   translateActions();
}
void MainMenu::createActions()
{
    //创建菜单项
    login = new QAction(this);
    dbset = new QAction(this);
    dbManage=new QAction(this);

    this->addAction(login);
    this->addAction(dbset);
    this->addAction(dbManage);
    connect(login, SIGNAL(triggered()), this, SIGNAL(showlogindia()));
    connect(dbset, SIGNAL(triggered()), this, SIGNAL(showdbset()));
    connect(dbManage, SIGNAL(triggered()), this, SIGNAL(showdbManage()));


}
void MainMenu::translateActions()
{
    login->setText(CH("登录"));
    dbset->setText(CH("设置"));
    dbManage->setText(CH("数据管理"));
}
