#ifndef ALARMSUBSTATION_H
#define ALARMSUBSTATION_H

#include <substationdata.h>
class AlarmSubstation
{
public:
    AlarmSubstation();
    void setId(int i)
    {
        id=i;
    }
    void setDataId(int i)
    {
        dataid=i;
    }
    void setStatus(int i)
    {
        status=i;
    }
    void setUid(int i)
    {
        uid=i;
    }
    void setChangeTime(const QString& time)
    {
        changeTime=time;
    }
    void setData(Substationdata* d)
    {
        data=d;
    }
    void setUserName(const QString &user)
    {
        userName=user;
    }

    int getId()const
    {
        return id;
    }
    int getDataid()const
    {
        return dataid;
    }
    int getStatus()const
    {
        return status;
    }
    int getUid()const
    {
        return uid;
    }
    const QString& getChangeTime()const
    {
        return changeTime;
    }
    const Substationdata* getData()const
    {
        return data;
    }
    const QString &getUserName()const
    {
        return userName;
    }
private:
    int id;
    int dataid;
    int status;
    int uid;
    QString changeTime;
    Substationdata *data;
    QString userName;
};

#endif // ALARMSUBSTATION_H
