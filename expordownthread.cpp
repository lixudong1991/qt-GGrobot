#include "expordownthread.h"

Expordownthread::Expordownthread()
{

}
Expordownthread::~Expordownthread()
{
    if(isRunning())
   {
        mutex.lock();
        e=false;
        cond.wakeOne();
        mutex.unlock();
        wait();     
    }
}
/***********************************************************************************
������:
��������:	�����������ͼƬ�����߳�
�������:
�������:
����ֵ:
************************************************************************************/
void  Expordownthread::run()
{ 

    QSettings ftpconfig("db.ini",QSettings::IniFormat);
    QString ip= ftpconfig.value("ftpserver/ip").toString();
    int port =ftpconfig.value("ftpserver/port").toInt();
    QString user= ftpconfig.value("ftpserver/user").toString();
    QString pwd=ftpconfig.value("ftpserver/pwd").toString();
    while(true)
    {
           mutex.lock();
           LOGI("exportdownthread wait");
           cond.wait(&mutex);
            if(!e)
            {
               mutex.unlock();
               break;
            }
            LOGI("exportdownthread ftp download: "<<EXPORTPATH.toStdString()<<filename.toStdString());
            FtpManager ftpmanager;
            ftpmanager.setHostPort(ip, port);
            ftpmanager.setUserInfo(user ,pwd);
            ftpmanager.setFilename(filename);
            connect(&ftpmanager,SIGNAL(finishe(QString)),this,SLOT(download()));
            ftpmanager.get(EXPORTPATH+filename);      
            exec();
            LOGI("exportdownthread  exec");
            mutex.unlock();
    }
    LOGI("exportdownthread exit");
}
/***********************************************************************************
������:
��������:	ͼƬ�������ʱ�����ź�
�������:
�������:
����ֵ:
************************************************************************************/
void Expordownthread::download()
{
        LOGI("exportdownthread download finished: "<<filename.toStdString());
        emit finish(filename);
        exit();
}

