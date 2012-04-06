#include "Dash.h"
/////////////////////////////////////////////////
Dash::Dash() : DashCleaner()
{

}
/////////////////////////////////////////////////
Value Dash::get(const std::string& key)
{
    Value result;

    kvstoreMutex.lock();
    result = kvstore[key];
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

    v.count++;
    v.value = value;
    v.setDirty(true);

    kvstore[key] = v;

    kvstoreMutex.unlock();
}
/////////////////////////////////////////////////
KVStore Dash::getDirtyValues()
{
    KVStore result;

    KVStore::iterator itr = kvstore.begin();
    for (; itr != kvstore.end(); itr++) {
        if (itr->second.isDirty() )
            result.insert(std::pair<std::string, Value>(itr->first, itr->second) );
    }

    return result;

}
/////////////////////////////////////////////////
std::vector< std::string > Dash::getKeys()
{
    std::vector<std::string> result;

    KVStore::iterator itr = kvstore.begin();
    for (; itr != kvstore.end(); itr++)
        result.push_back(itr->first);

    return result;
}
/////////////////////////////////////////////////
// TODO: implement / revisit this idea
void Dash::clean(DashCleaner *&dc) {
    if (dc) {
        dc->clean(NULL);
    }
}
/////////////////////////////////////////////////
Dash::~Dash()
{

}
/////////////////////////////////////////////////
