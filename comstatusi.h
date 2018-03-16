#ifndef COMSTATUSI_H
#define COMSTATUSI_H

#include <QObject>
#include "comstatusice.h"
#include "head.h"
class ComstatusI:public QObject,public interfaceICE::ComStatusICE
{
    Q_OBJECT
public:
     ComstatusI();
     void sportsCMDStatus(::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) override;
signals:
     void cmdStatus(int,int);
};
#endif // COMSTATUSI_H
