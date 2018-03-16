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
            LOGE("ice 初始化失败 : "<<e.what());
    }
}
IceCommunicatorFactory::~IceCommunicatorFactory()
{
}
void IceCommunicatorFactory::init()
{
    try
    {
         ic= Ice::initialize();
         adapte  =  ic->createObjectAdapterWithEndpoints ("CmdStatusAdapter", "default -p 10000");
    }
    catch(const Ice::Exception &e)
    {
            LOGE("ice 初始化失败 : "<<e.what());
    }

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
void  IceCommunicatorFactory::destory()
{
    if(adapte)
    {
         adapte->destroy();
         LOGI("IceCommunicatorFactory  adapter destory");
    }
    if(ic)
    {
         ic->destroy();
         LOGI("IceCommunicatorFactory  ic destory" );
    }
    LOGI("IceCommunicatorFactory +++++++++++");
}
