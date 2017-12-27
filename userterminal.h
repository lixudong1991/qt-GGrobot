#ifndef USERTERMINAL_H
#define USERTERMINAL_H

#include "head.h"
class Userterminal
{
public:
    Userterminal();
  void setId(int i)
  {
     id=i;
  }
  void setCreateDate(const QString &date)
  {
      createDate=date;
  }
  void setModifDate(const QString &date)
  {
      modifDate=date;
  }
  void setUserId(int i)
  {
      userid=i;
  }
  void setTerminalId(const QString &i)
  {
      terminalId=i;
  }
  void setTerminalIp(const QString &i)
  {
      terminalIp=i;
  }
  void setTerminalPort(const QString &i)
  {
      terminalPort=i;
  }
  void setCloudIp(const QString &i)
  {
      cloudIp=i;
  }
  void setCloudPort(const QString &i)
  {
      cloudPort=i;
  }
  void setCloudUser(const QString &i)
  {
      cloudUser=i;
  }
  void setCloudPwd(const QString &i)
  {
      cloudPwd=i;
  }
  void setOwnerUnit(const QString &i)
  {
       ownerUnit=i;
  }
  void setRemark(const QString &i)
  {
      remark=i;
  }
  int getId()const
  {
      return id;
  }
  const QString& getCreateDate()const
  {
      return createDate;
  }
  const QString& getModifDate()const
  {
      return modifDate;
  }
  int getUserid()const
  {
      return userid;
  }
  const QString& getTerminalId()const
  {
      return terminalId;
  }
  const QString& getTerminalIp()const
  {
      return terminalIp;
  }
  const QString& getTerminalPort()const
  {
      return terminalPort;
  }
  const QString& getCloudIp()const
  {
      return cloudIp;
  }
  const QString& getCloudPort()const
  {
      return cloudPort;
  }
  const QString& getCloudUser()const
  {
      return cloudUser;
  }
  const QString& getCloudPwd()const
  {
      return cloudPwd;
  }
  const QString& getOwnerUnit()const
  {
      return ownerUnit;
  }
  const QString& getRemark()const
  {
      return remark;
  }
  void setPosSize(int pos)
  {
      posSize=pos;
  }
 int getPosSize()const
 {
     return posSize;
 }
private:
  int id;
  QString createDate;
  QString modifDate;
  int userid;
  QString terminalId;
  QString terminalIp;
  QString terminalPort;
  QString cloudIp;
  QString cloudPort;
  QString cloudUser;
  QString cloudPwd;
  QString ownerUnit;
  QString remark;
  int posSize;
};

#endif // USERTERMINAL_H
