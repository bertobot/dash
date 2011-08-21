#include "Dash.h"
/////////////////////////////////////////////////
Dash::Dash()
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

    kvstore[key] = v;

    kvstoreMutex.unlock();
}
/////////////////////////////////////////////////
Dash::~Dash()
{

}
/////////////////////////////////////////////////
