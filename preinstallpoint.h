#ifndef PREINSTALLPOINT_H
#define PREINSTALLPOINT_H

#include <QString>
class PreinstallPoint
{
public:
    PreinstallPoint();
    void setPosName(const QString &s)
    {
        this->posName=s;
    }
    const QString &getPosName()const
    {
        return this->posName;
    }
    void setSonPosName(const QString &s)
    {
        this->sonPosName=s;
    }
    const QString &getSonPosName()const
    {
        return this->sonPosName;
    }
    void setCheckName(const QString &s)
    {
        this->checkName=s;
    }
    const QString &getCheckName()const
    {
        return this->checkName;
    }
    void setCheckType(int i)
    {
        this->checkType=i;
    }
    int getCheckType()const
    {
        return this->checkType;
    }
    void setAlarmTemp(int i)
    {
        this->alarmTemp=i;
    }
    int getAlarmTemp()const
    {
        return alarmTemp;
    }
    void setPos(int i)
    {
        this->pos=i;
    }
    int getPos()const
    {
        return pos;
    }
    void setSonPos(int i)
    {
        this->sonPos=i;
    }
    int getSonPos()const
    {
        return sonPos;
    }
private:
    QString posName;
    QString sonPosName;
    QString checkName;
    int checkType;
    int alarmTemp;
    int pos;
    int sonPos;
};

#endif // PREINSTALLPOINT_H
