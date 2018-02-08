#ifndef THREAD_H
#define THREAD_H
#include "head.h"
#include "ftpmanager.h"
#include <QMutexLocker>
#include <QMutex>
#include <QThread>
#include "substationdata.h"
#include "preinstallpoint.h"
class  Thread: public QThread
{
    Q_OBJECT
 public:
    Thread();
    ~Thread();
    void tStart();
    void setTerminalId(const QString&s)
    {
        QMutexLocker locker(&mutex);
        terminalId=s;
    }
    void setPointInfo(QHash<int,PreinstallPoint*> *p)
    {
        this->preinstallPointMap=p;
    }

 signals:
    void finish(Substationdata*,QList<int>*);
    void queryErr();
private slots:
    void download();
    void timeout();
 protected:
    void run();
private:
    QString terminalId;
    QMutex mutex;
    QTimer *timer;
    Substationdata data;
    QList<int> ids;
    QHash<int,PreinstallPoint*> *preinstallPointMap;

    volatile bool exit_t=true;
};

#endif // THREAD_H
