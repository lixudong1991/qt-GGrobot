#ifndef SPORTSCTRTHREAD_H
#define SPORTSCTRTHREAD_H
#include "head.h"
#include <QThread>
#include <QMutexLocker>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <Ice/Ice.h>
#include "GGRobotSession.h"
#include "GGSmart.h"
#include "comstatusi.h"
class SportsCtrThread:public QThread
{
    Q_OBJECT
public:
    SportsCtrThread();
    ~SportsCtrThread();
    void setProxyArg(const QString &a)
    {
        arg=a;
    }
    void iceSendCommand(const QString &c )
    {
        mutex.lock();
        com=c;
        cond.wakeOne();
        mutex.unlock();
    }
signals:
    void execComStatus(int);
protected:
   void run();
public slots:
   void cmdstatusslot(int,int);
private:
    QString arg;
    QString com;
    QWaitCondition cond;
    QMutex mutex;
    volatile bool exit_t=true;
};

#endif // SPORTSCTRTHREAD_H
