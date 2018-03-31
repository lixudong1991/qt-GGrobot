#include "alarmstatusthread.h"
#include "head.h"

AlarmStatusThread::AlarmStatusThread()
{

}
void AlarmStatusThread::run()
{

     if(alarmids.size()==0)
     {
          return;
     }
     QSqlQuery query;
     QString sql="UPDATE tbl_alarm SET alarmstatus=1,uid=";
                 sql.append(QString::number(userid));
                 sql.append(",changetime=NOW() WHERE id IN (");
      for(int i=0;i<alarmids.size()-1;i++)
      {
          sql.append(alarmids.at(i)+",");
      }
      sql.append(alarmids.last()+")");
      bool tem=false;
      mutex.lock();
      tem=query.exec(sql);
      if(!tem)
      {
          LOGE("execute sql  : "<<sql.toStdString()<<" error:  "<<query.lastError().text().toStdString());
          QSettings ftpconfig("db.ini",QSettings::IniFormat);
          QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
          db.setHostName(ftpconfig.value("database/ip").toString());
          db.setPort(ftpconfig.value("database/port").toInt());
          db.setUserName(ftpconfig.value("database/user").toString());
          db.setPassword(ftpconfig.value("database/pwd").toString());
          db.setDatabaseName(ftpconfig.value("database/db").toString());
          if(!db.open())
          {
               LOGE("重新创建数据库连接失败 AlarmStatusThread exit");
               mutex.unlock();
               return;
          }
           LOGE("重新创建数据库连接成功");
           tem=query.exec(sql);
      }
      mutex.unlock();
      if( tem)
      {
          emit updatastatus(0);
          LOGI("AlarmStatusThread sql"<<sql.toStdString()<<"  success");
      }else{
          emit updatastatus(-1);
          LOGE("AlarmStatusThread sql"<<sql.toStdString()<<"  failed");
      }
}
