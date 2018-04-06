#ifndef STATUSDATA_H
#define STATUSDATA_H

#include <QString>
class StatusData
{
public:
    StatusData();
    inline void setId(int i)
    {
        id=i;
    }
    inline void setTerminalId(const QString &s)
    {
        terminalId=s;;
    }
   inline  void setReportTime(const QString &s)
    {
        reportTime=s;;
    }
    inline void setWriteTime(const QString &s)
    {
        writeTime=s;;
    }
    inline int getId()const
    {
        return id;
    }
    inline const QString &getTerminalId()const
    {
        return terminalId;
    }
    inline const QString &getReportTime()const
    {
        return reportTime;
    }
    inline const QString &getWriteTime()const
    {
        return writeTime;
    }
    inline void setElectricitys(int i)
    {
       electricitys=i;
    }
    inline int getElectricitys()const
    {
        return electricitys;
    }
    inline void setVoltage(int i)
    {
       voltage=i;
    }
    inline int getVoltage()const
    {
        return voltage;
    }
    inline void setElectricResidue(int i)
    {
       electricResidue=i;
    }
    inline int getElectricResidue()const
    {
        return electricResidue;
    }
    inline void setRobotWorkMode(int i)
    {
       robotWorkMode=i;
    }
   inline  int getRobotWorkMode()const
    {
        return robotWorkMode;
    }
    inline void setRobotStatus(int i)
    {
       robotStatus=i;
    }
   inline  int getRobotStatus()const
    {
        return robotStatus;
    }
   inline  void setRadarFront(int i)
    {
      radarFront=i;
    }
    inline int getRadarFront()const
    {
        return radarFront;
    }
    inline void setRadarBack(int i)
    {
      radarBack=i;
    }
    inline int getRadarBack()const
    {
        return radarBack;
    }
    inline void setMagnetismFront(int i)
    {
      magnetismFront=i;
    }
    inline int getMagnetismFront()const
    {
        return magnetismFront;
    }
    inline void setMagnetismBack (int i)
    {
      magnetismBack =i;
    }
    inline  int getMagnetismBack ()const
    {
        return magnetismBack ;
    }
    inline  void setCardReader (int i)
    {
       cardReader =i;
    }
    inline int getCardReader ()const
    {
        return cardReader ;
    }
    inline void setAutoDoor (int i)
    {
       autoDoor =i;
    }
    inline int getAutoDoor()const
    {
        return autoDoor ;
    }
   inline  void setCharger (int i)
    {
       charger =i;
    }
    inline int getCharger()const
    {
        return charger ;
    }
private:
    int id;
    QString terminalId ;
    QString reportTime;
    QString writeTime;
    int electricitys ;
    int voltage ;
    int electricResidue  ;
    int robotWorkMode;
    int robotStatus;
    int radarFront;
    int radarBack;
    int magnetismFront ;
    int magnetismBack ;
    int cardReader;
    int autoDoor;
    int charger;
};

#endif // STATUSDATA_H
