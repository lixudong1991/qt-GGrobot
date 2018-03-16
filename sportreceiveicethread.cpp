#include "sportreceiveicethread.h"
#include "icecommunicatorfactory.h"
#include "comstatusi.h"
#include <Ice/Ice.h>
SportReceiveICEthread::SportReceiveICEthread()
{

}
SportReceiveICEthread::~SportReceiveICEthread()
{
}
 void SportReceiveICEthread::run()
 {
    Ice::CommunicatorPtr ic=IceCommunicatorFactory::getInstance()->communicator();
    Ice::ObjectAdapterPtr adapter =IceCommunicatorFactory::getInstance()->adapter();
     try {
         ComstatusI *cm=new ComstatusI();
          Ice::ObjectPtr object=cm;
          connect(cm,SIGNAL(cmdStatus(int,int)),this,SLOT(cmdstatusslot(int,int)));
          adapter->add (object, ic->stringToIdentity ("CmdStatus"));
          adapter->activate();
        //  exec();
          ic->waitForShutdown();
      }
      catch (const Ice::Exception& ex) {
          LOGE("adapter error: "<<ex.what());
      }
 }
 void SportReceiveICEthread::cmdstatusslot(int cmd,int status)
 {
     LOGI("cmdstatusslot==:"<<cmd<<"   "<<status);
     emit comStatus(cmd, status);
 }
