#ifndef SUBSTATIONDATA_H
#define SUBSTATIONDATA_H

#include <QString>
class Substationdata
{
public:
    Substationdata();
    void setDataId(int i)
    {
       dataId=i;
    }
    void setTerminalId(const QString &s)
    {
        terminalId=s;;
    }
    void setReportTime(const QString &s)
    {
        reportTime=s;;
    }
    void setWriteTime(const QString &s)
    {
        writeTime=s;;
    }
    void setPos(int i)
    {
       pos=i;
    }
    void setSonPos(int i)
    {
       sonPos=i;
    }
    void setDatatype(int i)
    {
       datatype=i;
    }
    void setData(int i)
    {
       data=i;
    }
    void setPictureType(int i)
    {
       pictureType=i;
    }
    void setPictureName(const QString &s)
    {
        pictureName=s;;
    }

    int getDataId()const
    {
        return dataId;
    }
    const QString &getTerminalId()const
    {
        return terminalId;
    }
    const QString &getReportTime()const
    {
        return reportTime;
    }
    const QString &getWriteTime()const
    {
        return writeTime;
    }
    int getPos()const
    {
        return pos;
    }
    int getSonPos()const
    {
        return sonPos;
    }
    int getDatatype()const
    {
        return datatype;
    }
    int getData()const
    {
        return data;
    }
    int getPictureType()const
    {
        return pictureType;
    }
    const QString &getPictureName()const
    {
        return pictureName;
    }
private:
    int dataId;
    QString terminalId;
    QString reportTime;
    QString writeTime;
    int pos;
    int sonPos;
    int datatype;
    int data;
    int pictureType;
    QString pictureName;
};

#endif // SUBSTATIONDATA_H
