#ifndef __NodeMap_h_
#define __NodeMap_h_
/////////////////////////////////////////////////
#include <MyThread/mutex.h>
#include <map>
#include "../common/utils.h"
#include "ProxyNodeSocket.h"
/////////////////////////////////////////////////
class NodeMap {
protected:
    std::map<std::string, ProxyNodeSocket*> nodeMap;
    mutex mapmutex;

public:
    NodeMap();

    bool addnode(const std::string &, ProxyNodeSocket *&);
    bool dropnode(const std::string &);
    std::vector<std::string> listnodes(const std::string &);
    ProxyNodeSocket * getnode(const std::string &);

    void sendToAll(const std::string &);
    void setToFirst(const std::string &);

    virtual ~NodeMap();
};
/////////////////////////////////////////////////
#endif
