#ifndef ALARMSTATUSTHREAD_H
#define ALARMSTATUSTHREAD_H

#include <QThread>
#include <QMutex>
class AlarmStatusThread : public QThread
{
    Q_OBJECT
public:
    AlarmStatusThread();
    void setUserid(int user)
    {
        this->userid=user;
    }
    void setAlarmids(const QStringList &ids)
    {
        this->alarmids=ids;
    }

signals:
    void updatastatus(int);
protected:
    void run();
private:
    int userid;
    QStringList alarmids;
     QMutex mutex;
};

#endif // ALARMSTATUSTHREAD_H
