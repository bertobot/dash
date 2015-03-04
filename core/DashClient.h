#ifndef __DashClient_h_
#define __DashClient_h_

#include <MySocket/ClientSocket.h>
#include <MySocket/BufferedReader.h>

#include <sstream>

class DashClient {
public:
    DashClient(ClientSocket *client) { mClient = client; }

    virtual ~DashClient() { mClient = NULL; }

    void put(const std::string &key, const std::string &value);

    std::string get(const std::string &key);

private:
    ClientSocket *mClient;

};

#endif
