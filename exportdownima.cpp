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
void ExportDownima::timeout()
{
    timer->stop();
    LOGE("-----------loading timeout-----------");
    loading_widget->start(false);
    QMessageBox::critical(this,"error",CH("程序错误"));
    emit error();
    this->close();
}

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

