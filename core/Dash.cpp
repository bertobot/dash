#include "Dash.h"
/////////////////////////////////////////////////
Dash::Dash()
{

}
/////////////////////////////////////////////////
std::string Dash::get(const std::string& key)
{
    std::string result;

    kvstoreMutex.lock();
    result = kvstore[key];
    kvstoreMutex.unlock();
    
    return result;
}
/////////////////////////////////////////////////
void Dash::put(const std::string& key, const std::string& value)
{
    kvstoreMutex.lock();
    
    kvstore[key] = value;

    kvstoreMutex.unlock();
}
/////////////////////////////////////////////////
Dash::~Dash()
{

}
/////////////////////////////////////////////////
