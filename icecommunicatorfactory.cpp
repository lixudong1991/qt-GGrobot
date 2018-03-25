#include "icecommunicatorfactory.h"
#include "log4z.h"

IceCommunicatorFactory::IceCommunicatorFactory()
{
    try
    {
         ic= Ice::initialize();
         adapte  =  ic->createObjectAdapterWithEndpoints ("CmdStatusAdapter", "default -p 10000");
    }
    catch(const Ice::Exception &e)
    {
            LOGE("ice ��ʼ��ʧ�� : "<<e.what());
    }
}
IceCommunicatorFactory::~IceCommunicatorFactory()
{
}

IceCommunicatorFactory* IceCommunicatorFactory::instance=new IceCommunicatorFactory();

IceCommunicatorFactory*  IceCommunicatorFactory::getInstance()
{
    return instance;
}

Ice::CommunicatorPtr  IceCommunicatorFactory::communicator()
{
    return ic;
}
Ice::ObjectAdapterPtr  IceCommunicatorFactory::adapter()
{
    return adapte;
}
