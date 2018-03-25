#ifndef ICECOMMUNICATORFACTORY_H
#define ICECOMMUNICATORFACTORY_H
#include <Ice/Ice.h>

class IceCommunicatorFactory
{
public:
    static  IceCommunicatorFactory * getInstance();
    Ice::CommunicatorPtr communicator();
    Ice::ObjectAdapterPtr adapter();
    ~IceCommunicatorFactory();
private:
    IceCommunicatorFactory();
    IceCommunicatorFactory(const IceCommunicatorFactory&);
    IceCommunicatorFactory& operator=(const IceCommunicatorFactory&);

    static IceCommunicatorFactory* instance;

    Ice::CommunicatorPtr ic=nullptr;
    Ice::ObjectAdapterPtr adapte=nullptr;
};

#endif // ICECOMMUNICATORFACTORY_H
