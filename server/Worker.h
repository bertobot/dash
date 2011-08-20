#ifndef __Worker_h_
#define __Worker_h_

#include "../core/Dash.h"
#include "ThreadWriter.h"

#include <MyThread/thread.h>
#include <MySocket/Select.h>
#include <MySocket/ServerSocket.h>
#include <libstrmanip++/utils.h>

#include <iostream>
#include <vector>
#include <errno.h>
#include <string.h>

class Worker : public thread {
protected:
    bool shutdownflag;
    ThreadWriter *tw;
    Dash *dash;

    ServerSocket *server;
    Socket *client;
    int workerId;

public:
    Worker(ServerSocket *server);

    void stop();
    int close();

    void run();

    void setThreadWriter(ThreadWriter*);
    void setDash(Dash *);
    virtual void processRequest();
    virtual bool challenge();

    void printLocal(const std::string&);
    void respond(const std::string&);
    void printLocalAndRespond(const std::string&);

    void setWorkerId(int id);
    int getWorkerId() const;
    
    virtual ~Worker();
};

#endif
