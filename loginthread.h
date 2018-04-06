#ifndef LOGINTHREAD_H
#define LOGINTHREAD_H

#include "head.h"
#include "userterminal.h"
class  LoginThread: public QThread
{
    Q_OBJECT
 public:
    LoginThread();
    ~LoginThread();
    void setDevicesList(QList<Userterminal> *devices )
    {
        userDevices=devices;
    }
signals:
    void logstatus(int);
private slots:

protected:
    void run();
public:
   bool createDbConnect();
   QString ip;
   int port;
   QString username;
   QString password;
   QString dbna;
   QMutex mutex;
   QString user;
   QString pwd;
   QList<Userterminal> *userDevices;
   void  alarmTempSave(Userterminal*);
};
#endif // LOGINTHREAD_H
