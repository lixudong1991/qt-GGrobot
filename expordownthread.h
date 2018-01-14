#ifndef EXPORTDOWNTHREAD_H
#define EXPORTDOWNTHREAD_H
#include "head.h"
#include "ftpmanager.h"
#include <QMutexLocker>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
class  Expordownthread: public QThread
{
    Q_OBJECT
 public:
    Expordownthread();
    ~Expordownthread();
    void setName(const QString &s)
    {
        mutex.lock();
        filename=s;
        mutex.unlock();
    }
    void wakeT()
    {
        mutex.lock();
        cond.wakeOne();
        mutex.unlock();
    }
    void exitexec()
    {
        LOGI("exportdownthread download timeout:"<<filename.toStdString());
        emit finish(filename);
        exit();
    }

signals:
     void finish(QString);
private slots:
     void download();
   //  void error(QNetworkReply::NetworkError);
 protected:
    void run();
private:
    QString filename;
    QWaitCondition cond;
    QMutex mutex;
    volatile bool e=true;
};

#endif // THREAD_H
