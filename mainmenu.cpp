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
    dbManage=new QAction(this);
    this->addAction(dbManage);
    connect(dbManage, SIGNAL(triggered()), this, SIGNAL(showdbManage()));
}
void MainMenu::translateActions()
{
    dbManage->setText(CH("数据管理"));
}
