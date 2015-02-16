#ifndef __DashClient_h_
#define __DashClient_h_

#include <MySocket/ClientSocket.h>

#include <sstream>

class DashClient {
protected:
    ClientSocket *client;

public:
    //DashClient();
    DashClient(ClientSocket *client);

    void put(const std::string &key, const std::string &value);
    std::string get(const std::string &key);

    virtual ~DashClient();
};

#endif
