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
    bool dirty;

    Value() {
        count = 0;
        timestamp = time(NULL);
    }

    bool isEmpty() {
	return value.empty();
    }

    bool isDirty() {
        return dirty;
    }

    void setDirty(bool b) {
        dirty = b;
    }

    virtual ~Value() {

    }
};

// abstract class to handle cleaning of dirty pages.
class DashCleaner {
public:
    virtual void clean(void *param) { }
};

typedef std::map<std::string, Value> KVStore;

class Dash : public DashCleaner {
protected:
    KVStore kvstore;
    mutex kvstoreMutex;

public:
    Dash();

    void put(const std::string &key, const std::string &value);
    Value get(const std::string &key);

    KVStore getDirtyValues();

    virtual void clean(DashCleaner *&dc);

    std::vector<std::string> getKeys();

    virtual ~Dash();
};

#endif
