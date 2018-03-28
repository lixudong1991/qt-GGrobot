#ifndef FILEDOWNTHREAD_H
#define FILEDOWNTHREAD_H
#include "head.h"
#include "ftpmanager.h"
#include <QMutexLocker>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
class  Filedownthread: public QThread
{
    Q_OBJECT
 public:
    Filedownthread();
    ~Filedownthread();
    void downloadFile(const QString &s)
    {
        mutex.lock();
        filename=s;
        cond.wakeOne();
        mutex.unlock();
    }
    void exitexec()
    {
        LOGI("Filedownthread download timeout:"<<filename.toStdString());
        exit();
    }
signals:
     void finish(QString);
     void error();
private slots:
     void download();
 protected:
    void run();
private:
    QString filename;
    QWaitCondition cond;
    QMutex mutex;
    volatile bool e=true;
};

#endif // THREAD_H
