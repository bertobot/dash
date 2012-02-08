#ifndef __ProxySocket_h_
#define __ProxySocket_h_

#include "ThreadSocket.h"
#include "NodeMap.h"

/////////////////////////////////////////////////
class ProxySocket : public ThreadSocket {
private:
    NodeMap *nm;

public:
    ProxySocket(const Socket &rhs);

    virtual void stop();

    bool addNode(const std::vector<std::string> &);
    void dropNode(const std::vector<std::string> &);
    void listNodes(const std::vector<std::string> &);

    void passItDown(const std::string &);

    void assocNodeMap(NodeMap *);

    virtual ~ProxySocket();
};

#endif
