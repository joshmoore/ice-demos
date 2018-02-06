// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Callback.h>

using namespace std;
using namespace Demo;

class CallbackReceiverI : public CallbackReceiver
{
public:

    virtual void
    callback(Ice::Int num, const Ice::Current&)
    {
        cout << "received callback #" << num << endl;
    }
};

class CallbackClient : public Ice::Application
{
public:

    virtual int run(int, char*[]);
};

int
main(int argc, char* argv[])
{
#ifdef ICE_STATIC_LIBS
    Ice::registerIceWS();
#endif

    CallbackClient app;
    return app.main(argc, argv, "config.client");
}

int
CallbackClient::run(int argc, char*[])
{
    if(argc > 1)
    {
        cerr << appName() << ": too many arguments" << endl;
        return 1;
    }

    CallbackSenderPrx server = CallbackSenderPrx::checkedCast(communicator()->propertyToProxy("CallbackSender.Proxy"));
    if(!server)
    {
        cerr << appName() << ": invalid proxy" << endl;
        return 1;
    }

    Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("");
    Ice::Identity ident;
    ident.name = Ice::generateUUID();
    ident.category = "";
    CallbackReceiverPtr cr = new CallbackReceiverI;
    adapter->add(cr, ident);
    adapter->activate();
    server->ice_getConnection()->setAdapter(adapter);
    server->addClient(ident);
    communicator()->waitForShutdown();

    return 0;
}