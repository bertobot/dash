#ifndef __ProxyWorker_h_
#define __ProxyWorker_h_

#include "Worker.h"
#include <map>
#include <MySocket/ClientSocket.h>

class ProxyWorker : public Worker {
protected:
    std::map<std::string, ClientSocket> *map;
    int timeout;

public:
    ProxyWorker(ServerSocket *server);

    void processRequest();

    void associateMap(std::map<std::string, ClientSocket> *m);

    virtual ~ProxyWorker();
};

#endif
