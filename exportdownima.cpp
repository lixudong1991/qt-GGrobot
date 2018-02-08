#include "exportdownima.h"

ExportDownima::ExportDownima(QWidget *parent)
    : Dialog(parent)
{
    resize(200, 100);
    loading_widget = new LoadingWidget(this);
    QHBoxLayout *h=new QHBoxLayout(this);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    h->addWidget(loading_widget);
}

ExportDownima::~ExportDownima()
{

}
/***********************************************************************************
函数名:
函数描述:	图片下载等待界面超时处理函数
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportDownima::timeout()
{
    timer->stop();
    LOGE("-----------loading timeout-----------");
    loading_widget->start(false);
   // QMessageBox::critical(this,"error",CH("程序错误"));
    emit error();
    this->close();
}
/***********************************************************************************
函数名:
函数描述:	图片下载loading界面启动和停止
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportDownima::loadingStart(bool b,const QString &mess)
{
    if(b)
    {//CH("正在下载图片")
         loading_widget->setAccount(mess);
         loading_widget->start(true);
         timer->start(60000);
         this->exec();
    }
    else{
        loading_widget->start(false);
        timer->stop();
        this->close();
    }
}

