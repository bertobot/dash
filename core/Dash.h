#ifndef __Dash_h_
#define __Dash_h_

#include <MyThread/mutex.h>

#include <map>
#include <string>



typedef std::map<std::string, std::string> KVStore;

class Dash {
protected:
    KVStore kvstore;
    mutex kvstoreMutex;

public:
    Dash();

    void put(const std::string &key, const std::string &value);
    std::string get(const std::string &key);

    virtual ~Dash();
};

#endif
