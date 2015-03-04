#ifndef __ProxyCommand_h_
#define __ProxyCommand_h_

#include <MySocket/ClientSocket.h>
#include <ControlPort/Command.h>
#include <map>

#include <stdlib.h>

typedef std::map<std::string, ClientSocket> NamedChannelMap;

class ProxyCommand : public Command {
public:
    ProxyCommand(NamedChannelMap *ncmap) : Command("proxy", "clusters dash instances.") { mMap = ncmap; }

    virtual ~ProxyCommand() { mMap = NULL; }

    std::string execute(const std::vector< std::string >& list);

private:
    NamedChannelMap *mMap;
};

#endif
// vim: ts=4:sw=4:expandtab
