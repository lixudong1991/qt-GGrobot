#include "thread.h"
#include <QSqlError>
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
/***********************************************************************************
函数名:
函数描述:	 图像界面定时扫描线程
输入参数:
输出参数:
返回值:
************************************************************************************/
void  Thread::run()
{
   QSettings ftpconfig("db.ini",QSettings::IniFormat);
   QString ftpip = ftpconfig.value("ftpserver/ip").toString();
   int ftpport = ftpconfig.value("ftpserver/port").toInt();
   QString ftpuser = ftpconfig.value("ftpserver/user").toString();
   QString ftppwd = ftpconfig.value("ftpserver/pwd").toString();
   int time=ftpconfig.value("picture/refurbishtime").toInt();
    LOGI("thread1 scanner space time:"<<time<<" second" );
   QSqlQuery query;
   mutex.lock();
   if(query.exec("SELECT NOW()")&&query.next())
   {
        beginTime=query.value(0).toDateTime().toString(DATEFORMAT);
        LOGI("thread1 scanner beginTime:"<<beginTime.toStdString() );
   }
   mutex.unlock();
   while(exit_t)
   {   
       QString statussql="SELECT * FROM tbl_statusdata WHERE terminalId='";
       statussql.append(terminalId);
       statussql.append("' AND writeTime >= '");
       statussql.append(beginTime);
       statussql.append("' ORDER BY writeTime DESC");
       bool tem=false;
       mutex.lock();
       tem=query.exec(statussql);
       mutex.unlock();
       data.setDataId(-1);
       StatusData *statu=data.getRobotStatus();
       if(statu!=nullptr)
       {
           delete statu;
       }
       data.setRobotStatus(nullptr);
       if (tem&&query.next())
       {

            statu=new StatusData();
            statu->setId(query.value(0).toInt());
            statu->setTerminalId(query.value(1).toString());
            statu->setReportTime(query.value(2).toDateTime().toString(DATEFORMAT));
            statu->setWriteTime(query.value(3).toDateTime().toString(DATEFORMAT));
            statu->setElectricitys(query.value(4).toInt());
            statu->setVoltage(query.value(5).toInt());
            statu->setElectricResidue(query.value(6).toInt());
            statu->setRobotStatus(query.value(7).toInt());
            statu->setRadarFront(query.value(8).toInt());
            statu->setMagnetismFront(query.value(9).toInt());
            statu->setMagnetismBack(query.value(10).toInt());
            statu->setCardReader(query.value(11).toInt());
            statu->setAutoDoor(query.value(12).toInt());
            statu->setCharger(query.value(13).toInt());
            data.setRobotStatus(statu);
            LOGI("StatusData id:"<<statu->getId());
       }
       query.prepare("SELECT * FROM tbl_substationdata WHERE terminalId=:id AND writeTime > (SELECT SUBDATE(NOW(),INTERVAL :time SECOND)) ORDER BY writeTime DESC");
       query.bindValue(":id",terminalId);
       query.bindValue(":time",QString::number(time+1));
       mutex.lock();
       tem=query.exec();
       mutex.unlock();
       if(!tem)
       {
           LOGE("execute select sql error : "<<query.lastError().text().toStdString());
           if(query.lastError().type()==QSqlError::ConnectionError)
           {
                 emit queryErr();
                 LOGE("thread exit");
                 break;
           }
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
           ids.clear();
           while(query.next())
           {
                ids.append(query.value(4).toInt());
           }
           if(data.getDatatype()==2)
           {
               QHash<int,PreinstallPoint*>::const_iterator iter;
               iter=preinstallPointMap->find(data.getSonPos());
               if(iter!=preinstallPointMap->cend()&&iter.value()->getAlarmTemp()<=data.getData())
               {
                    QString sql="INSERT INTO tbl_alarm VALUE(DEFAULT,";
                    sql.append(QString::number(data.getDataId()));
                    sql.append(",DEFAULT,");
                    sql.append(QString::number(-1));
                    sql.append(",NOW())");
                    LOGI("find a Alarm,sql: "<<sql.toStdString());
                    mutex.lock();
                    tem=query.exec(sql);
                    mutex.unlock();
                    if(!tem)
                    {
                        LOGE("execute sql  : "<<sql.toStdString()<<" error:  "<<query.lastError().text().toStdString());
                    }
               }
           }
           if(data.getPos()>=2000)
           {
               FtpManager ftpmanager;
               ftpmanager.setHostPort(ftpip, ftpport);
               ftpmanager.setUserInfo(ftpuser, ftppwd);
               ftpmanager.setFilename(data.getPictureName());
               connect(&ftpmanager, SIGNAL(finishe(QString)), this, SLOT(download()));
               ftpmanager.get(FILECACHEPATH+data.getPictureName());
               exec();
           }else{
               emit finish(&data,&ids);
               exec();
           }
          LOGI("thread1 scanner image -->name: "<<data.getPictureName().toStdString()<<"  type:"<<data.getPictureType()<<"  time:"<<data.getReportTime().toStdString()<<" pos:"<<data.getPos());
       }
       else
       {
           emit finish(&data,&ids);
           exec();
       }

   }
    LOGI("thread1 exit");

}
void  Thread::download()
{
     LOGI("thread1 ftpget finish: "<<data.getPictureName().toStdString());
     emit finish(&data,&ids);
 }
void Thread::timeout()
{
    exit();
}
void Thread::tStart()
{
//    qDebug()<<CH("线程启动");
    LOGI("thread1 start------------------------------------------------------------------------------------------------>");
    start();
    QSettings timeconfig("db.ini",QSettings::IniFormat);
    timer->start(timeconfig.value("picture/refurbishtime").toInt()*1000);
}
