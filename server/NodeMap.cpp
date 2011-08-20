#include "NodeMap.h"
/////////////////////////////////////////////////
NodeMap::NodeMap() {

}
/////////////////////////////////////////////////
bool NodeMap::addnode(const std::string &str, ProxyNodeSocket *&c) {
    mapmutex.lock();

    std::map<std::string, ProxyNodeSocket*>::iterator nmitr = nodeMap.find(str);
    if (nmitr != nodeMap.end() ) {
        return false;
    }
    nodeMap[str] = c;

    mapmutex.unlock();

    return true;
}
/////////////////////////////////////////////////
bool NodeMap::dropnode(const std::string &str) {
    mapmutex.lock();

    bool result = false;

    std::map<std::string, ProxyNodeSocket*>::iterator nmitr = nodeMap.find(str);
    if (nmitr != nodeMap.end() ) {
        nodeMap.erase(nmitr);
        result = true;
    }

    mapmutex.unlock();

    return result;
}
/////////////////////////////////////////////////
 std::vector<std::string> NodeMap::listnodes(const std::string &str) {
     // TODO: use str as regex (to be implemented)
     mapmutex.lock();

     std::vector<std::string> result;
     std::map<std::string, ProxyNodeSocket*>::iterator nmitr = nodeMap.begin();
     for(; nmitr != nodeMap.end(); nmitr++) {
         result.push_back(nmitr->first);
     }

     mapmutex.unlock();

     return result;
}
/////////////////////////////////////////////////
ProxyNodeSocket * NodeMap::getnode(const std::string &name) {
    mapmutex.lock();
    ProxyNodeSocket *cs = nodeMap[name];
    mapmutex.unlock();

    return cs;
}
/////////////////////////////////////////////////
void NodeMap::sendToAll(const std::string &str) {

    mapmutex.lock();

    ProxyNodeSocket *pns;
    std::map<std::string, ProxyNodeSocket*>::iterator nmitr = nodeMap.begin();
    for(; nmitr != nodeMap.end(); nmitr++) {
        pns = nmitr->second;
        pns->write(str);
    }

    mapmutex.unlock();
}
/////////////////////////////////////////////////
void NodeMap::setToFirst(const std::string &str) {
    ProxyNodeSocket *cs;
    std::map<std::string, ProxyNodeSocket*>::iterator nmitr = nodeMap.begin();

    // TODO: setToFirst sets a 'main' node.  a kind of strategy.
}
/////////////////////////////////////////////////
NodeMap::~NodeMap() {

}
/////////////////////////////////////////////////
