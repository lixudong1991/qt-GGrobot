#ifndef THREAD_H
#define THREAD_H
#include "head.h"
#include "ftpmanager.h"
#include <QMutexLocker>
#include <QMutex>
#include <QThread>
#include "substationdata.h"
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

 signals:
    void finish(Substationdata*);
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
    volatile bool exit_t=true;
};

#endif // THREAD_H
