#ifndef ALARMQUERYTHREAD_H
#define ALARMQUERYTHREAD_H
#include <QList>
#include <QThread>
#include "alarmsubstation.h"
class AlarmQueryThread : public QThread
{
    Q_OBJECT
public:
    AlarmQueryThread();
    void setDeviceId(const QString &i)
    {
        deviceId=i;
    }
    void setStartTime(const QString &i)
    {
        starttime=i;
    }
    void setStopTime(const QString &i)
    {
        stoptime=i;
    }
    volatile bool queryall=false;
signals:
    void queryfinish(QList<AlarmSubstation*>*);
protected:
    void run();
private:
    QString deviceId;
    QString starttime;
    QString stoptime;

    QList<AlarmSubstation*> *datas=nullptr;
};

#endif // ALARMQUERYTHREAD_H
