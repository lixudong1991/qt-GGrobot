#include "thread.h"
#include <QDebug>

Thread::Thread()
{
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
}
Thread::~Thread()
{
    timer->stop();   
    exit_t=false;
    exit();
    wait();
}

void  Thread::run()
{
   QSettings ftpconfig("db.ini",QSettings::IniFormat);
   QString ftpip = ftpconfig.value("ftpserver/ip").toString();
   int ftpport = ftpconfig.value("ftpserver/port").toInt();
   QString ftpuser = ftpconfig.value("ftpserver/user").toString();
   QString ftppwd = ftpconfig.value("ftpserver/pwd").toString();
   QString time=ftpconfig.value("picture/refurbishtime").toString();
    LOGI("thread1 scanner space time:"<<time.toStdString()<<" second" );
   while(exit_t)
   {   
       QSqlQuery query;
       query.prepare("SELECT * FROM tbl_substationdata WHERE terminalId=:id AND reportTime > (SELECT SUBDATE(NOW(),INTERVAL :time SECOND)) ORDER BY reportTime DESC");
       query.bindValue(":id",terminalId);
       query.bindValue(":time",time);
       if(!query.exec())
       {
          emit queryErr();
           break;
       }

       if(query.next())
       {
           {
               QMutexLocker locker(&mutex);
               data.setDataId(query.value(0).toInt());
               data.setTerminalId(query.value(1).toString());
               data.setReportTime(query.value(2).toDateTime().toString(DATEFORMAT));
               data.setWriteTime(query.value(3).toDateTime().toString(DATEFORMAT));
               data.setPos(query.value(4).toInt());
               data.setSonPos(query.value(5).toInt());
               data.setDatatype(query.value(6).toInt());
               data.setData(query.value(7).toInt());
               data.setPictureType(query.value(8).toInt());
               data.setPictureName(query.value(9).toString());
           }
           FtpManager ftpmanager;
           ftpmanager.setHostPort(ftpip, ftpport);
           ftpmanager.setUserInfo(ftpuser, ftppwd);
           ftpmanager.setFilename(data.getPictureName());
           connect(&ftpmanager, SIGNAL(finishe(QString)), this, SLOT(download()));
           ftpmanager.get(FILECACHEPATH+data.getPictureName());
           exec();
          LOGI("thread1 scanner image -->name: "<<data.getPictureName().toStdString()<<"  type:"<<data.getPictureType()<<"  time:"<<data.getReportTime().toStdString());
       }
       else
       {
           exec();
       }

   }
    LOGI("thread1 exit");

}
void  Thread::download()
{
    LOGI("thread1 ftpget finish: "<<data.getPictureName().toStdString());
     emit finish(&data);
 }
void Thread::timeout()
{
    exit();
}
void Thread::tStart()
{
//    qDebug()<<CH("Ïß³ÌÆô¶¯");
    LOGI("thread1 start------------------------------------------------------------------------------------------------>");
    start();
    QSettings timeconfig("db.ini",QSettings::IniFormat);
    timer->start(timeconfig.value("picture/refurbishtime").toInt()*1000);
}
