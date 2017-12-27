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
   bool con=false;
   bool createDbConnect();
   QString ip;
   int port;
   QString username;
   QString password;
   QString dbna;

   QString user;
   QString pwd;
   QList<Userterminal> *userDevices;
};
#endif // LOGINTHREAD_H
