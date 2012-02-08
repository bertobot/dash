#ifndef __Dash_h_
#define __Dash_h_

#include <MyThread/mutex.h>

#include <vector>
#include <map>
#include <string>

class Value {
public:
    unsigned int count;
    unsigned int timestamp;    
    std::string value;

    Value() {
	count = 0;
	timestamp = time(NULL);
    }

    bool isEmpty() {
	return value.empty();
    }

    virtual ~Value() {

    }
};

typedef std::map<std::string, Value> KVStore;

class Dash {
protected:
    KVStore kvstore;
    mutex kvstoreMutex;

public:
    Dash();

    void put(const std::string &key, const std::string &value);
    Value get(const std::string &key);

    std::vector<std::string> getKeys();

    virtual ~Dash();
};

#endif
