#ifndef __MetricHash_h_
#define __MetricHash_h_

#include "../common/utils.h"
#include <MyThread/mutex.h>
#include <map>
#include <set>

class MetricHash {

protected:
    std::set<std::string> originals;
    std::map<std::string, MetricHash> hash;

    void addHash(std::map<std::string, MetricHash> &, std::queue<std::string> &);
    std::vector<std::string> getKey(std::map<std::string, MetricHash> &, std::queue<std::string> &);
	std::map<std::string, MetricHash> & getHash();

	mutex mhlock;

public:
    MetricHash();

    void addMetricKey(const std::string&);
    std::vector<std::string> getMetricKey(const std::string&);

    std::set<std::string> getOriginals() ;

    virtual ~MetricHash();
};

#endif

