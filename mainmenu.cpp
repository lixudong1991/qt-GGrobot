#include "mainmenu.h"
MainMenu::MainMenu(QWidget *widget)
    : QMenu(widget)
{
   createActions();
   translateActions();
}
void MainMenu::createActions()
{
    //�����˵���
    dbManage=new QAction(this);
    this->addAction(dbManage);
    connect(dbManage, SIGNAL(triggered()), this, SIGNAL(showdbManage()));
}
void MainMenu::translateActions()
{
    dbManage->setText(CH("���ݹ���"));
}
