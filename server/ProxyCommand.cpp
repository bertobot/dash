#include "ProxyCommand.h"

std::string ProxyCommand::execute(const std::vector< std::string >& list)
{
// TODO: log this error
if (! mMap)
    return "error: map is null.";

if (list.size() < 2)
    return "usage:\nproxy add <host> <port> <alias>\nproxy del <alias>";

if (list[1] == "add") {
    if (list.size() != 5)
	return "usage: proxy add <host> <port> <alias>";

    ClientSocket cs(list[2], atoi(list[3].c_str()) );
    mMap->insert(std::pair<std::string, ClientSocket>(list[4], cs) );

    return "added " + list[4] + ".";
}
else if (list[1] == "del") {
    if (list.size() != 3)
	return "usage: proxy del <alias>";

    NamedChannelMap::iterator itr = mMap->find(list[2]);

    if (itr == mMap->end() )
	return "alias " + list[2] + " not found.";

    mMap->erase(itr);

    return "removed " + list[2] + ".";
}
else if (list[1] == "list") {
    std::string response;
    NamedChannelMap::iterator itr = mMap->begin();
    for (; itr != mMap->end(); itr++)
	response += itr->first + "\n";

    return response;
}

else 
    return "usage:\nproxy add <host> <port> <alias>\nproxy del <alias>";
}

// vim: ts=4:sw=4:expandtab
