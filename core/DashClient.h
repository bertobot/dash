#ifndef __DashClient_h_
#define __DashClient_h_

#include <map>
#include <string>

typedef std::map<std::string, std::string> KVStore;

class DashClient {
protected:
    KVStore kvstore;

public:
    DashClient();

    void put(const std::string &key, const std::string &value);
    std::string get(const std::string &key);

    virtual ~DashClient();
};

#endif
