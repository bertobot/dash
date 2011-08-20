#ifndef __Worker_h_
#define __Worker_h_

#include "Worker.h"

class ProxyWorker : public Worker {
protected:
	std::vector<Socket*> *remotes;

public:
	ProxyWorker(ServerSocket *server);

    void run();
    void processRequest();

    void associateRemotes(std::vector<Socket*> *remotes);

    virtual ~Worker();
};

#endif
