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
private:
    KVStore kvstore;
    
    mutex kvstoreMutex;

    long int ageLimit;
    
    long int countLimit;
    

public:
    Dash(long int age = -1, long int count = -1);

    void put(const std::string &key, const std::string &value);
    
    Value get(const std::string &key);

    /**
     * This method is an administrator 'get', fetching the value
     * without affecting the counter.  This is for stats reporting,
     * and not for fetching.
     */
    Value peek(const std::string &key);
    
    void remove(const std::string &key);


    KVStore getDirtyValues();

    KVStore getValuesByAge(unsigned int age);

    KVStore getValuesByCount(unsigned int count);


    void removeValuesByAge(unsigned int age);

    void removeValuesByCount(unsigned int count);
    

    void clear();   
  

    virtual void clean(DashCleaner *&dc);

    std::vector<std::string> getKeys();

    void setAgeLimit(long int limit);

    void setCountLimit(long int limit);

    long int getAgeLimit() const;

    long int getCountLimit() const;


    virtual ~Dash();
};

#endif
