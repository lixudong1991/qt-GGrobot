#ifndef SPORTSCTRTHREAD_H
#define SPORTSCTRTHREAD_H
#include "head.h"
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
    void iceSendCommand(const QString &c)
    {
        mutex.lock();
        com=c;
        sendCard=false;
        cond.wakeOne();
        mutex.unlock();
    }
    void iceSendCommand(const QString &c,const QString &card)
    {
        mutex.lock();
        com=c;
        cards=card;
        sendCard=true;
        cond.wakeOne();
        mutex.unlock();
    }
protected:
   void run();
signals:
    void execComStatus(QString);
private:
    QString arg;
    QString com;
    QString cards;
    QWaitCondition cond;
    QMutex mutex;
    volatile bool exit_t=true;
    bool sendCard=false;
};

#endif // SPORTSCTRTHREAD_H
