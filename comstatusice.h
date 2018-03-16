// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.6.3
//
// <auto-generated>
//
// Generated from file `comstatusice.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __d__documents_visual_studio_2015_Projects_ConsoleApplication1_ConsoleApplication1_generated_comstatusice_h__
#define __d__documents_visual_studio_2015_Projects_ConsoleApplication1_ConsoleApplication1_generated_comstatusice_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Proxy.h>
#include <Ice/GCObject.h>
#include <Ice/AsyncResult.h>
#include <Ice/Incoming.h>
#include <IceUtil/ScopedArray.h>
#include <IceUtil/Optional.h>
#include <Ice/StreamF.h>
#include <IceUtil/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 306
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 3
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace interfaceICE
{

class ComStatusICE;
void __read(::IceInternal::BasicStream*, ::IceInternal::ProxyHandle< ::IceProxy::interfaceICE::ComStatusICE>&);
::IceProxy::Ice::Object* upCast(::IceProxy::interfaceICE::ComStatusICE*);

}

}

namespace interfaceICE
{

class ComStatusICE;
::Ice::Object* upCast(::interfaceICE::ComStatusICE*);
typedef ::IceInternal::Handle< ::interfaceICE::ComStatusICE> ComStatusICEPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::interfaceICE::ComStatusICE> ComStatusICEPrx;
void __patch(ComStatusICEPtr&, const ::Ice::ObjectPtr&);

}

namespace interfaceICE
{

class Callback_ComStatusICE_sportsCMDStatus_Base : virtual public ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_ComStatusICE_sportsCMDStatus_Base> Callback_ComStatusICE_sportsCMDStatusPtr;

}

namespace IceProxy
{

namespace interfaceICE
{

class ComStatusICE : virtual public ::IceProxy::Ice::Object
{
public:

    void sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status)
    {
        sportsCMDStatus(__p_com, __p_status, 0);
    }
    void sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::Ice::Context& __ctx)
    {
        sportsCMDStatus(__p_com, __p_status, &__ctx);
    }
#ifdef ICE_CPP11
    ::Ice::AsyncResultPtr
    begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::IceInternal::Function<void ()>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception = ::IceInternal::Function<void (const ::Ice::Exception&)>(), const ::IceInternal::Function<void (bool)>& __sent = ::IceInternal::Function<void (bool)>())
    {
        return begin_sportsCMDStatus(__p_com, __p_status, 0, new ::IceInternal::Cpp11FnOnewayCallbackNC(__response, __exception, __sent));
    }
    ::Ice::AsyncResultPtr
    begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& __completed, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& __sent = ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>())
    {
        return begin_sportsCMDStatus(__p_com, __p_status, 0, ::Ice::newCallback(__completed, __sent), 0);
    }
    ::Ice::AsyncResultPtr
    begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::Ice::Context& __ctx, const ::IceInternal::Function<void ()>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception = ::IceInternal::Function<void (const ::Ice::Exception&)>(), const ::IceInternal::Function<void (bool)>& __sent = ::IceInternal::Function<void (bool)>())
    {
        return begin_sportsCMDStatus(__p_com, __p_status, &__ctx, new ::IceInternal::Cpp11FnOnewayCallbackNC(__response, __exception, __sent), 0);
    }
    ::Ice::AsyncResultPtr
    begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::Ice::Context& __ctx, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& __completed, const ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>& __sent = ::IceInternal::Function<void (const ::Ice::AsyncResultPtr&)>())
    {
        return begin_sportsCMDStatus(__p_com, __p_status, &__ctx, ::Ice::newCallback(__completed, __sent));
    }
#endif

    ::Ice::AsyncResultPtr begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status)
    {
        return begin_sportsCMDStatus(__p_com, __p_status, 0, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::Ice::Context& __ctx)
    {
        return begin_sportsCMDStatus(__p_com, __p_status, &__ctx, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_sportsCMDStatus(__p_com, __p_status, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::Ice::Context& __ctx, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_sportsCMDStatus(__p_com, __p_status, &__ctx, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::interfaceICE::Callback_ComStatusICE_sportsCMDStatusPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_sportsCMDStatus(__p_com, __p_status, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_sportsCMDStatus(::Ice::Int __p_com, ::Ice::Int __p_status, const ::Ice::Context& __ctx, const ::interfaceICE::Callback_ComStatusICE_sportsCMDStatusPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_sportsCMDStatus(__p_com, __p_status, &__ctx, __del, __cookie);
    }

    void end_sportsCMDStatus(const ::Ice::AsyncResultPtr&);
    
private:

    void sportsCMDStatus(::Ice::Int, ::Ice::Int, const ::Ice::Context*);
    ::Ice::AsyncResultPtr begin_sportsCMDStatus(::Ice::Int, ::Ice::Int, const ::Ice::Context*, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& __cookie = 0);
    
public:
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_adapterId(const ::std::string& __id) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_locatorCacheTimeout(int __timeout) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_connectionCached(bool __cached) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_secure(bool __secure) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_preferSecure(bool __preferSecure) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_collocationOptimized(bool __co) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_invocationTimeout(int __timeout) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_invocationTimeout(__timeout).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_twoway() const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_oneway() const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_batchOneway() const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_datagram() const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_batchDatagram() const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_compress(bool __compress) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_timeout(int __timeout) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_connectionId(const ::std::string& __id) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    }
    
    ::IceInternal::ProxyHandle<ComStatusICE> ice_encodingVersion(const ::Ice::EncodingVersion& __v) const
    {
        return dynamic_cast<ComStatusICE*>(::IceProxy::Ice::Object::ice_encodingVersion(__v).get());
    }
    
    static const ::std::string& ice_staticId();

private: 
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace interfaceICE
{

class ComStatusICE : virtual public ::Ice::Object
{
public:

    typedef ComStatusICEPrx ProxyType;
    typedef ComStatusICEPtr PointerType;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void sportsCMDStatus(::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___sportsCMDStatus(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

protected:
    virtual void __writeImpl(::IceInternal::BasicStream*) const;
    virtual void __readImpl(::IceInternal::BasicStream*);
    using ::Ice::Object::__writeImpl;
    using ::Ice::Object::__readImpl;
};

inline bool operator==(const ComStatusICE& l, const ComStatusICE& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

inline bool operator<(const ComStatusICE& l, const ComStatusICE& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

}

namespace interfaceICE
{

template<class T>
class CallbackNC_ComStatusICE_sportsCMDStatus : public Callback_ComStatusICE_sportsCMDStatus_Base, public ::IceInternal::OnewayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)();

    CallbackNC_ComStatusICE_sportsCMDStatus(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallbackNC<T>(obj, cb, excb, sentcb)
    {
    }
};

template<class T> Callback_ComStatusICE_sportsCMDStatusPtr
newCallback_ComStatusICE_sportsCMDStatus(const IceUtil::Handle<T>& instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_ComStatusICE_sportsCMDStatus<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_ComStatusICE_sportsCMDStatusPtr
newCallback_ComStatusICE_sportsCMDStatus(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_ComStatusICE_sportsCMDStatus<T>(instance, 0, excb, sentcb);
}

template<class T> Callback_ComStatusICE_sportsCMDStatusPtr
newCallback_ComStatusICE_sportsCMDStatus(T* instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_ComStatusICE_sportsCMDStatus<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_ComStatusICE_sportsCMDStatusPtr
newCallback_ComStatusICE_sportsCMDStatus(T* instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_ComStatusICE_sportsCMDStatus<T>(instance, 0, excb, sentcb);
}

template<class T, typename CT>
class Callback_ComStatusICE_sportsCMDStatus : public Callback_ComStatusICE_sportsCMDStatus_Base, public ::IceInternal::OnewayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const CT&);

    Callback_ComStatusICE_sportsCMDStatus(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallback<T, CT>(obj, cb, excb, sentcb)
    {
    }
};

template<class T, typename CT> Callback_ComStatusICE_sportsCMDStatusPtr
newCallback_ComStatusICE_sportsCMDStatus(const IceUtil::Handle<T>& instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_ComStatusICE_sportsCMDStatus<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_ComStatusICE_sportsCMDStatusPtr
newCallback_ComStatusICE_sportsCMDStatus(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_ComStatusICE_sportsCMDStatus<T, CT>(instance, 0, excb, sentcb);
}

template<class T, typename CT> Callback_ComStatusICE_sportsCMDStatusPtr
newCallback_ComStatusICE_sportsCMDStatus(T* instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_ComStatusICE_sportsCMDStatus<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_ComStatusICE_sportsCMDStatusPtr
newCallback_ComStatusICE_sportsCMDStatus(T* instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_ComStatusICE_sportsCMDStatus<T, CT>(instance, 0, excb, sentcb);
}

}

#include <IceUtil/PopDisableWarnings.h>
#endif
