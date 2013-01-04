#include "Dash.h"
/////////////////////////////////////////////////
Dash::Dash(long int ageLimit, long int countLimit) : DashCleaner()
{
    this->ageLimit = ageLimit;

    this->countLimit = countLimit;
}
/////////////////////////////////////////////////
Value Dash::get(const std::string& key)
{
    Value result;

    kvstoreMutex.lock();
    
    result = kvstore[key];

    ++kvstore[key].count;

    if ( countLimit != -1 && kvstore[key].count > countLimit )
        kvstore.erase(key);

    if ( ageLimit != -1 && (time(NULL) - kvstore[key].timestamp) > ageLimit)
        kvstore.erase(key);
    
    kvstoreMutex.unlock();

    return result;
}
/////////////////////////////////////////////////
void Dash::put(const std::string& key, const std::string& value)
{
    kvstoreMutex.lock();

    Value v;

    if (! kvstore[key].isEmpty() )
	v = kvstore[key];

    // TODO: need separate put and get counts?
    
    v.count = 0;
    v.value = value;
    v.setDirty(true);

    kvstore[key] = v;

    kvstoreMutex.unlock();
}
/////////////////////////////////////////////////
KVStore Dash::getDirtyValues()
{
    KVStore result;

    kvstoreMutex.lock();

    KVStore::iterator itr = kvstore.begin();
    for (; itr != kvstore.end(); itr++) {
        if (itr->second.isDirty() )
            result.insert(std::pair<std::string, Value>(itr->first, itr->second) );
    }

    kvstoreMutex.unlock();

    return result;

}
/////////////////////////////////////////////////
std::vector< std::string > Dash::getKeys()
{
    std::vector<std::string> result;

    kvstoreMutex.lock();

    KVStore::iterator itr = kvstore.begin();
    for (; itr != kvstore.end(); itr++)
        result.push_back(itr->first);

    kvstoreMutex.unlock();

    return result;
}
/////////////////////////////////////////////////
// TODO: implement / revisit this idea
void Dash::clean(DashCleaner *&dc) {
    if (dc) {
        dc->clean(NULL);
    }
}

void Dash::clear()
{
    kvstoreMutex.lock();

    kvstore.clear();

    kvstoreMutex.unlock();
}

KVStore Dash::getValuesByAge(unsigned int age)
{
    KVStore result;

    kvstoreMutex.lock();

    KVStore::iterator itr = kvstore.begin();
    for (; itr != kvstore.end(); itr++) {
        if (itr->second.timestamp > age)
            result.insert(std::pair<std::string, Value>(itr->first, itr->second) );
    }

    kvstoreMutex.unlock();

    return result;
}

KVStore Dash::getValuesByCount(unsigned int count)
{
    KVStore result;

    kvstoreMutex.lock();
    
    KVStore::iterator itr = kvstore.begin();
    for (; itr != kvstore.end(); itr++) {
        if (itr->second.count > count)
            result.insert(std::pair<std::string, Value>(itr->first, itr->second) );
    }

    kvstoreMutex.unlock();

    return result;
}

void Dash::remove(const std::string& key)
{
    kvstoreMutex.lock();

    kvstore.erase(key);

    kvstoreMutex.unlock();    
}

void Dash::removeValuesByAge(unsigned int age)
{
    kvstoreMutex.lock();

    KVStore::iterator itr = kvstore.begin();
    while (itr != kvstore.end() ) {
        if (itr->second.timestamp > age) {
            kvstore.erase(itr);

            // TODO: test this - I'm not sure if this works as expected.
            itr++;
        }
    }

    kvstoreMutex.unlock();
}

void Dash::removeValuesByCount(unsigned int count)
{
    kvstoreMutex.lock();

    KVStore::iterator itr = kvstore.begin();
    while (itr != kvstore.end() ) {
        if (itr->second.count > count) {
            kvstore.erase(itr);

            // TODO: test this - I'm not sure if this works as expected.
            itr++;
        }
    }

    kvstoreMutex.unlock();
}

long int Dash::getAgeLimit() const
{
    return ageLimit;
}

long int Dash::getCountLimit() const
{
    return countLimit;
}

void Dash::setAgeLimit(long int limit)
{
    ageLimit = limit;
}

void Dash::setCountLimit(long int limit)
{
    countLimit = limit;
}

Value Dash::peek(const std::string& key)
{
    Value result;
    
    kvstoreMutex.lock();

    result = kvstore[key];
    
    kvstoreMutex.unlock();

    return result;
}


/////////////////////////////////////////////////
Dash::~Dash()
{
    clear();
}
/////////////////////////////////////////////////
