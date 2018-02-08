#include "loginthread.h"

LoginThread::LoginThread()
{

}
LoginThread::~LoginThread()
{

}
/***********************************************************************************
函数名:
函数描述:	 登陆查询线程
输入参数:
输出参数:
返回值:
************************************************************************************/
void LoginThread::run()
{
    if(!con)
    {
        if(!createDbConnect())
        {
            emit logstatus(-1);
            return;
        }
        con=true;
    }
    QSqlQuery query;
    query.prepare("select userid from tbl_users where userName=:user and userPwd=:pwd");
    query.bindValue(":user",user);
    query.bindValue(":pwd",pwd);
    query.exec();
    if(query.next())
    {
        int userid=query.value(0).toInt();
        QSqlQuery query;
        query.prepare("select * from tbl_userterminal where userid=:id");
        query.bindValue(":id",userid);
        query.exec();
        while(query.next())
        {
            Userterminal userdevice;
            userdevice.setId(query.value(0).toInt());
            userdevice.setCreateDate(query.value(1).toDateTime().toString(DATEFORMAT));
            userdevice.setModifDate(query.value(2).toDateTime().toString(DATEFORMAT));
            userdevice.setUserId(query.value(3).toInt());
            userdevice.setTerminalId(query.value(4).toString());
            userdevice.setTerminalIp(query.value(5).toString());
            userdevice.setTerminalPort(query.value(6).toString());
            userdevice.setCloudIp(query.value(7).toString());
            userdevice.setCloudPort(query.value(8).toString());
            userdevice.setCloudUser(query.value(9).toString());
            userdevice.setCloudPwd(query.value(10).toString());
            userdevice.setInfraredIp(query.value(11).toString());
            userdevice.setOwnerUnit(query.value(12).toString());
            userdevice.setRemark(query.value(13).toString());
            userdevice.setPosSize(query.value(14).toInt());
            alarmTempSave(&userdevice);
            userDevices->append(userdevice);
        }
        emit logstatus(userid);
    }
    else{
        emit logstatus(-1);
    }
}
bool LoginThread::createDbConnect()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ip);
    db.setPort(port);
    db.setUserName(username);
    db.setPassword(password);
    db.setDatabaseName(dbna);
    if(!db.open())
    {
    //    QMessageBox::critical(this,CH("错误"),db.lastError().text());
        return false;
    }
    return true;
}
void  LoginThread::alarmTempSave(Userterminal* term)
{
    QString fileName="map/"+term->getTerminalId()+".csv";
    LOGI("AlarmTemp load :"<< fileName.toStdString());
     if(fileName.isEmpty())
     {
         return;
     }
     QFile file(fileName);
     if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         return;
     }
     QTextStream in(&file);
     int i=0;
     while(!in.atEnd()&&i<2)
     {
         in.readLine();
         i++;
     }
     QHash<int,PreinstallPoint*>* p=term->getPointInfo();
     if(p!=nullptr)
     {
         QHash<int,PreinstallPoint*>::iterator iter;
         for(iter=p->begin(); iter!=p->end(); ++iter)
         {
             delete iter.value();
         }
         delete p;
     }
     QStringList list;
     p=new QHash<int,PreinstallPoint*>();
     term->setPointInfo(p);
     while(!in.atEnd())
     {
         QString fileLine = in.readLine();
         list = fileLine.split(",");
         PreinstallPoint *pos=new PreinstallPoint();
         pos->setPosName(list.at(1));
         pos->setSonPosName(list.at(2));
         pos->setCheckName(list.at(3));
         pos->setCheckType(list.at(4).toInt());
         pos->setAlarmTemp(list.at(5).toFloat()*100);
         pos->setPos(list.at(6).toInt());
         pos->setSonPos(list.at(7).toInt());
         p->insert(pos->getSonPos(),pos);
     //    LOGI(pos->getPosName().toStdString()<<", "<<pos->getSonPosName().toStdString()<<", "<<pos->getCheckName().toStdString()<<", "<<pos->getCheckType()<<", "<<pos->getAlarmTemp()<<", "<<pos->getPos()<<", "<<pos->getSonPos());
     }
     LOGI("p size: "<<p->size());
     file.close();
}
