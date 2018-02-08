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
      if(query.exec(sql))
      {
          emit updatastatus(0);
           LOGI("AlarmStatusThread sql"<<sql.toStdString()<<"  success");
      }else{
          emit updatastatus(-1);
           LOGI("AlarmStatusThread sql"<<sql.toStdString()<<"  failed");
      }
}
