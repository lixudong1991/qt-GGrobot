#include "loginthread.h"

LoginThread::LoginThread()
{

}
LoginThread::~LoginThread()
{

}
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
            userdevice.setOwnerUnit(query.value(11).toString());
            userdevice.setRemark(query.value(12).toString());
            userdevice.setPosSize(query.value(13).toInt());
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
    //    QMessageBox::critical(this,CH("´íÎó"),db.lastError().text());
        return false;
    }
    return true;
}
