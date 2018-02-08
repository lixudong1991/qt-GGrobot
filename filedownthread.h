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
