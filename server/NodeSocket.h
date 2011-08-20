#ifndef __NodeSocket_h_
#define __NodeSocket_h_

#include "ThreadSocket.h"
#include <MySocket/Select.h>
/////////////////////////////////////////////////
class NodeSocket : public ThreadSocket {

public:
    NodeSocket(const Socket &rhs);

    virtual void run();
    virtual void stop();

    virtual bool challenge();
    virtual void onLoop();

    virtual bool put(const std::vector<std::string> &);
    virtual void get(const std::vector<std::string> &);

    /*
    void list(const std::vector<std::string> &);
    void listall(const std::vector<std::string> &);
    void receipt(const std::vector<std::string> &);
    void usage();
    void counters();
    */

    virtual ~NodeSocket();
};

#endif
