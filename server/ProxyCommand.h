#ifndef __ProxyCommand_h_
#define __ProxyCommand_h_

#include <MySocket/ClientSocket.h>
#include <ControlPort/Command.h>
#include <map>

#include <stdlib.h>

class ProxyCommand : public Command {
protected:
    std::map<std::string, ClientSocket> *map;
    
public:
    ProxyCommand();

    std::string execute(const std::vector< std::string >& list);
    void associateMap(std::map<std::string, ClientSocket> *map);

    virtual ~ProxyCommand();
};

#endif
