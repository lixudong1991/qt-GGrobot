#include "alarmquerythread.h"
#include <QSqlQuery>
#include <QVariant>
#include "head.h"
AlarmQueryThread::AlarmQueryThread()
{

}
void AlarmQueryThread::run()
{
    QSqlQuery query;
    QString sql="SELECT alarm.*,substationid.*,`user`.userName FROM tbl_alarm AS alarm "
                "JOIN tbl_substationdata AS substationid ON alarm.`substationid`= substationid.`dataId` "
                "JOIN tbl_users AS `user` ON alarm.`uid`=`user`.`userid` "
                "WHERE substationid.`terminalId`='"+deviceId+"'";
    if(!queryall)
    {
        sql.append(" AND substationid.`writeTime`>='"+starttime+"' AND substationid.`writeTime`<='"+stoptime+"'");
    }

    if(datas!=nullptr)
    {
        for(AlarmSubstation * dat:*datas)
        {
            auto *subdat=dat->getData();
            delete subdat;
            delete dat;
        }
        delete datas;
        datas=nullptr;
    }
    LOGI("AlarmQueryThread sql: "<<sql.toStdString());
    if(query.exec(sql))
    {
        datas=new QList<AlarmSubstation*>();
        while(query.next())
        {
            AlarmSubstation *data=new AlarmSubstation();
            Substationdata *subdata=new Substationdata();
            data->setId(query.value(0).toInt());
            data->setDataId(query.value(1).toInt());
            data->setStatus(query.value(2).toInt());
            data->setUid(query.value(3).toInt());
            data->setChangeTime(query.value(4).toString());
            data->setData(subdata);

            subdata->setDataId(query.value(5).toInt());
            subdata->setTerminalId(query.value(6).toString());
            subdata->setReportTime(query.value(7).toString());
            subdata->setWriteTime(query.value(8).toString());
            subdata->setPos(query.value(9).toInt());
            subdata->setSonPos(query.value(10).toInt());
            subdata->setDatatype(query.value(11).toInt());
            subdata->setData(query.value(12).toInt());
            subdata->setPictureType(query.value(13).toInt());
            subdata->setPictureName(query.value(14).toString());

            data->setUserName(query.value(15).toString());
            datas->append(data);
        }
        LOGI("AlarmQueryThread Datas Size "<<datas->size());
    }
    emit queryfinish(datas);
}
