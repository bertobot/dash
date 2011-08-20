#include "MetricHash.h"
//////////////////////////////////////////////////
MetricHash::MetricHash() {

}
//////////////////////////////////////////////////
void MetricHash::addMetricKey(const std::string &str) {
	mhlock.lock();

    // keep a copy of the original
    originals.insert(str);

    // parse for tree
    std::queue<std::string> tokens = vectorToQueue(split('#', str) );
    addHash(hash, tokens);

	mhlock.unlock();
}
//////////////////////////////////////////////////
void MetricHash::addHash(std::map<std::string, MetricHash> &h, std::queue<std::string> & tokens) {
    if (tokens.empty() ) {
        return;
    }

    std::string key = tokens.front();
    MetricHash val;

    std::pair<std::string, MetricHash> npair(key, val);
    h.insert(npair);

    tokens.pop();

    // recurse
    addHash(h[key].getHash(), tokens);
}
//////////////////////////////////////////////////
std::vector<std::string> MetricHash::getMetricKey(const std::string &str) {
	mhlock.lock();

	std::vector<std::string> result;

    std::queue<std::string> q;
    if (! str.empty() )
        q = vectorToQueue(split('#', str) );

    result = getKey(hash, q);
	mhlock.unlock();

	return result;
}
//////////////////////////////////////////////////
std::vector<std::string> MetricHash::getKey(std::map<std::string, MetricHash> &h, std::queue<std::string> &tokens) {

    if (! h.empty() ) {

        // if there are no [more] tokens in the tuple, list the keys.
        if (tokens.empty() ) {
            std::vector<std::string> result;
            std::map<std::string, MetricHash>::iterator itr = h.begin();
            for (; itr != h.end(); itr++) {
                result.push_back(itr->first);
            }
            return result;
        }

        // recurse by getting h's hash, and passing the token tuple to this function
        MetricHash *subhash = &h[tokens.front()];
        tokens.pop();
        return getKey(subhash->getHash(), tokens);
    }

    std::vector<std::string> result;
    return result;
}
//////////////////////////////////////////////////
std::set<std::string> MetricHash::getOriginals() {
	std::set<std::string> result;

	mhlock.lock();
    result = originals;
	mhlock.unlock();

	return result;
}
//////////////////////////////////////////////////
std::map<std::string, MetricHash> & MetricHash::getHash() {
	return hash;
}
//////////////////////////////////////////////////
MetricHash::~MetricHash() {

}
//////////////////////////////////////////////////
