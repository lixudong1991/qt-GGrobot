#include "sportsctrthread.h"

SportsCtrThread::SportsCtrThread()
{

}
SportsCtrThread::~SportsCtrThread()
{
    mutex.lock();
    exit_t=false;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

void SportsCtrThread::run()
{
    Ice::CommunicatorPtr ic;
    ComstatusI *cmdstatus=new ComstatusI();
  //  connect(cmdstatus,SIGNAL(cmdStatus(int,int)),this,SLOT(cmdstatusslot(int,int)));
    try {
         // 初始化ICE运行时
         ic = Ice::initialize();
         Ice::ObjectAdapterPtr adapter  =  ic->createObjectAdapterWithEndpoints ("CmdStatusAdapter", "default -p 10000");
         Ice::ObjectPtr object =cmdstatus ;
         adapter->add (object, ic->stringToIdentity ("CmdStatusAdapter"));
         adapter->activate();
     }
     catch (const Ice::Exception& ex) {
         LOGE("Ice init Exception: "<<ex.what());
         return;
     }
    GGSmart::GGOrderMsgPtr ctrmsg =new GGSmart::GGOrderMsg();
    LOGI("sportsctrThread start");
    while(true)
    {
        mutex.lock();
        LOGI("sportsctrThread wait");
        cond.wait(&mutex);
        if(!exit_t)
        {
            mutex.unlock();
            LOGI("sportsctrThread exit");
            break;
        }
        try {
               Ice::ObjectPrx base = ic->stringToProxy(arg.toStdString().c_str());
               GGSmart::RobotCallbackPrx robotCtr= GGSmart::RobotCallbackPrx::checkedCast(base);
               ctrmsg->OderType=com.toStdString();
               if(!robotCtr)
               {
                  LOGE("Ice send "<<com.toStdString()<<"  Command error Proxy ");
                  emit execComStatus(-1);
               }
               else
               {
                  robotCtr->begin_doOrder(ctrmsg);
                  emit execComStatus(0);
                  LOGI("Ice send "<<com.toStdString()<<"  Command success ");
               }
         } catch (const Ice::Exception &ex){
            LOGE("Ice send "<<com.toStdString()<<"  Command Exception: "<<ex.what());
            emit execComStatus(-1);
        }
        mutex.unlock();
    }
    if (ic)
    ic->destroy();
}
 void SportsCtrThread::cmdstatusslot(int cmd,int status)
 {
     exit();
     LOGI("cmdstatusslot==:"<<cmd<<"   "<<status);
     if(status!=-1)
     {
         emit execComStatus(0);
         LOGI("Ice Command : "<<com.toStdString()<<" execute success");
     }else{
         emit execComStatus(-1);
         LOGI("Ice Command "<<com.toStdString()<<" execute failed");
     }
 }
