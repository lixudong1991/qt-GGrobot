#include "sportsctrthread.h"
#include "icecommunicatorfactory.h"
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
    Ice::CommunicatorPtr ic=IceCommunicatorFactory::getInstance()->communicator();
    Ice::ObjectAdapterPtr adapter =IceCommunicatorFactory::getInstance()->adapter();
    interfaceICE::ComStatusICEPrx comprx=interfaceICE::ComStatusICEPrx::uncheckedCast(adapter->createProxy(ic->stringToIdentity ("CmdStatus")));
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
              LOGI("sendcommand :"<<com.toStdString()<<" sportsctrThread------:"<<cards.toStdString());
               Ice::ObjectPrx base = ic->stringToProxy(arg.toStdString());
               GGSmart::RobotCallbackPrx robotCtr= GGSmart::RobotCallbackPrx::checkedCast(base->ice_timeout(5000));
               ctrmsg->OderType=com.toStdString();
               ctrmsg->ExData.erase("card");
               if(sendCard)
               {
                      ctrmsg->ExData.insert(std::make_pair("card",cards.toStdString()));
               }
               if(!robotCtr)
               {
                  LOGE("Ice send "<<com.toStdString()<<"  Command error Proxy ");
                  emit execComStatus("error");
               }
               else
               {
                  robotCtr->begin_doOrder(comprx,ctrmsg);
                  LOGI("Ice send "<<com.toStdString()<<"  Command success");
                  emit execComStatus(com);
               }
         } catch (const Ice::Exception &ex){
            LOGE("Ice send "<<com.toStdString()<< "  Command Exception: "<<ex.what());
            emit execComStatus("error");
        }
        mutex.unlock();
    }
    if (ic)
    ic->destroy();
}

