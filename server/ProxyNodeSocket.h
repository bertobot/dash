#ifndef __ProxyNodeSocket_h_
#define __ProxyNodeSocket_h_

#include <MySocket/ClientSocket.h>
#include <MyThread/thread.h>
#include <string>
#include "../common/utils.h"
/////////////////////////////////////////////////
class ProxyNodeSocket : public ClientSocket, public thread {
protected:
    int returnCode;
    std::string sendString;

public:
    ProxyNodeSocket(const ClientSocket &rhs);
    ProxyNodeSocket(const std::string &, int p);

    virtual void run();
    virtual void stop();

    bool isMetroUp();

    int write(const std::string &);

    void respond(const std::string &);
    void debugAndRespond(const std::string &);

    virtual ~ProxyNodeSocket();
};

#endif
