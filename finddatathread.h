#ifndef FINDDATATHREAD_H
#define FINDDATATHREAD_H

#include"head.h"
#include "substationdata.h"
#include "preinstallpoint.h"
class  FindDataThread: public QThread
{
    Q_OBJECT
 public:
    FindDataThread();
    ~FindDataThread();
    void setFilename(const QString&n)
    {
        name=n;
    }
    void setDeviceId(const QString &s)
    {
        deviceId=s;
    }
    void setStartTime(const QString &s)
    {
        starttime=s;
    }
    void setStopTime(const QString &s)
    {
        stoptime=s;
    }
    void setStartpos(const QString &s)
    {
        startpos=s;
    }
    void setStoppos(const QString &s)
    {
        stoppos=s;
    }
    bool  model=true;
    QHash<int,PreinstallPoint*> *preinstallPointMap;
signals:
    void  threadEnd(QMap<int,QList<Substationdata*>*>*);
private slots:

protected:
    void run();
private:
    QString name;
    QString deviceId;
    QString starttime;
    QString stoptime;
    QString startpos;
    QString stoppos;

    QMap<int,QList<Substationdata*>*> *datamap;


};
#endif // FINDDATATHREAD_H
