#ifndef SPORTRECEIVEICETHREAD_H
#define SPORTRECEIVEICETHREAD_H

#include <QThread>

class SportReceiveICEthread : public QThread
{
     Q_OBJECT
public:
    explicit  SportReceiveICEthread();
    ~SportReceiveICEthread();
signals:
     void comStatus(int,int);
protected:
   void run();
public slots:
   void cmdstatusslot(int,int);
private:
};

#endif // SPORTRECEIVEICETHREAD_H
