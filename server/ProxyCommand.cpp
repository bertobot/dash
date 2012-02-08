#include "ProxyCommand.h"

ProxyCommand::ProxyCommand()
{
    name = "proxy";
    map = NULL;
}

std::string ProxyCommand::execute(const std::vector< std::string >& list)
{
    // TODO: log this error
    if (! map)
        return "error: map is null.";

    if (list.size() < 2)
        return "usage:\nproxy add <host> <port> <alias>\nproxy del <alias>";
    
    if (list[1] == "add") {
        if (list.size() != 5)
            return "usage: proxy add <host> <port> <alias>";

        ClientSocket cs(list[2], atoi(list[3].c_str()) );
        map->insert(std::pair<std::string, ClientSocket>(list[4], cs) );

        return "added " + list[4] + ".";
    }
    else if (list[1] == "del") {
        if (list.size() != 3)
            return "usage: proxy del <alias>";

        std::map<std::string, ClientSocket>::iterator itr = map->find(list[2]);

        if (itr == map->end() )
            return "alias " + list[2] + " not found.";

        map->erase(itr);

        return "removed " + list[2] + ".";
    }
    else if (list[1] == "list") {
        std::string response;
        std::map<std::string, ClientSocket>::iterator itr = map->begin();
        for (; itr != map->end(); itr++)
            response += itr->first + "\n";

        return response;
    }

    else 
        return "usage:\nproxy add <host> <port> <alias>\nproxy del <alias>";
}

void ProxyCommand::associateMap(std::map< std::string, ClientSocket >* m)
{
    this->map = m;
}

ProxyCommand::~ProxyCommand()
{
    map = NULL;
}
